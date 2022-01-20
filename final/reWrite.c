#define XXH_INLINE_ALL
#define XXH_STATIC_LINKING_ONLY /* access advanced declarations */
#define XXH_IMPLEMENTATION      /* access definitions */
#define DEBUG 0
#define DEBUGN 30000
#define PULLOVER
#define sizeOfMem 128l * 1024l * 1024l
#define WordSize 4096 * 1024
#define SentenceSize 512 * 1024
#include "xxhash.h"
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <x86intrin.h>

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

uint8_t memRoot[sizeOfMem] __attribute__((aligned(16))) = {0};
uint8_t *mem = memRoot, *passageBuf, *stopWordBuf, *outBuf;
#define swap(a, b) \
    do             \
    {              \
        a ^= b;    \
        b ^= a;    \
        a ^= b;    \
    } while (0);
struct hashLinkList
{
    uint64_t hashNum; //last part of 64bits hash
    uint32_t next;    //location relative to memRoot
    uint32_t word;    //location relative to memRoot
    uint32_t n;
} * pHash;

uint32_t hashRecord[256l * 1024l] = {0}; //location relative to memRoot
uint32_t wordRecord[WordSize] = {0};

struct sentenceRecord
{
    uint32_t sentenceBegin;
    uint32_t sentenceEnd; //storage from start to end
    uint32_t wordStart;
    uint32_t wordEnd;
} sentenceRecord[SentenceSize] = {0};

struct nRecord
{
    uint32_t id;
    uint32_t n;
} sentenceN[SentenceSize] = {0};

uint32_t collitionTime = 0;
#if (DEBUG)
long long timeBuf;
#define showRunTime()                                                                                                     \
    do                                                                                                                    \
    {                                                                                                                     \
        long long time = clock();                                                                                         \
        timeBuf = time - timeBuf;                                                                                         \
        printf("from begin %lld ms, from last %lld ms\n", time * 1000 / CLOCKS_PER_SEC, timeBuf * 1000 / CLOCKS_PER_SEC); \
        timeBuf = time;                                                                                                   \
    } while (0);
#else
#define showRunTime() \
    do                \
    {                 \
        ;             \
    } while (0);
#endif
int cmp(const void *a, const void *b)
{
    //printf("ret : %d \n", ret);
    return (int)(((*((long long *)a) - *((long long *)b)) >> 32) | 1);
    ;
}
inline uint16_t Mystrcmp(char *a, char *b, uint32_t len)
{
#ifndef IGNOREHASHCOLLICTION
    if (a[len] != 0 || b[len] != 0)
        return 0;
    register uint64_t index = 0xFFFF;
    for (uint8_t i = 0; i < len; i += 16)
    {
        __asm__ __volatile__("movdqu (%1), %%xmm0\nmovdqu (%2), %%xmm1\npcmpistrm $0x08, %%xmm0, %%xmm1\npextrw $0, %%xmm0, %%r13\nandq %%r13, %0\n"
                             : "+r"(index)
                             : "rm"(a + i),
                               "rm"(b + i)
                             : "%xmm0", "%xmm1", "%r13");
        if (index != 0xFFFF)
            break;
    }
    /*if(ret != strcmp(a,b))
        {
            printf("%s %s %d %d dont match\n",a,b,ret,strcmp(a,b));
        }*/
    return ~(uint16_t)index;
#else
    return strcmp(a, b);
#endif
}

inline void printBin(uint16_t Oin)
{
    uint16_t in = Oin;
    for (uint8_t y = 0; y < 16; y++)
    {
        putchar('0' + (((1 << y) & in) ? 1 : 0));
    }
    putchar('\n');
}

inline void declaremMem(int size)
{
    mem += size;
}

inline void memAligned(int N, int position)
{
    declaremMem((N + position - ((uint32_t)mem % N)) % N);
}

uint32_t passageBufLenth, stopWordBufLength, outBufLength;
uint32_t wordNum = 0, wordNumMem[16] = {0}, wordBefore = 0, sentenceLeft = 0, sentenceNum = 0;
void processWord()
{
    register struct
    {
        uint16_t sentenceBeginMask;
        uint16_t gapMask;
        uint16_t sentenceMask;
        uint16_t wordMask;
    } mask, maskCopy;

    //mask allocation

    char upperMaskList[16] __attribute__((aligned(16))) = "AZ";
    char lowerMaskList[16] __attribute__((aligned(16))) = "az";
    char andMaskList[16] __attribute__((aligned(16))) = {
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
    char endSentenceMaskList[16] __attribute__((aligned(16))) = ".!?";
    char gapMaskList[16] __attribute__((aligned(16))) = {0x20, '\n'};

    register char *wordTemp = mem;
    declaremMem(WordSize);

    pHash = NULL;

    register char *inputPassage = passageBuf;
    register char *endOfPassage = passageBuf + passageBufLenth;
    memAligned(16, 0);
    outBuf = mem;
    char *pNowOutput = mem;
    declaremMem(16);
    register struct
    {
        uint8_t wordReadState;
        uint8_t sentenceState;
        uint8_t wordShift;
        uint8_t sentenceShift;
        uint8_t cpyLeft;
        uint8_t temp;
        uint8_t sentenceSiginalPosition;
        uint8_t extractedWordPosition;
    } flag = {0, 0, 0, 0, 0, 0, 0, 0};
    for (; inputPassage < endOfPassage; inputPassage += 16)
    {
        __asm__ __volatile__("pcmpistrm $0x44, %2, %3\n" // cmd, passage, range ->save mask result to xmm0
                             "pand  %4, %%xmm0\n"        // behind was the result
                             "paddb %%xmm0, %2\n"        // behind was the result
                             "movaps %2, %1\n"           // save the lower output

                             "movq $0, %0\n"              //reset
                             "pcmpistrm $0x04, %2, %5\n"  // generate character mask in xmm0's first word
                             "pextrw $0, %%xmm0, %%r15\n" // extra data from xmm0's first word and save to r15w register
                             "orq %%r15, %0\n"            // save data to "Mask"
                             "salq $16, %0\n"             // do a shift

                             "pcmpistrm $0x00, %2, %6\n"  // generate sentence mask in xmm0's first word
                             "pextrw $0, %%xmm0, %%r15\n" // extra data from xmm0's first word
                             "orq %%r15, %0\n"            // save data to "Mask"
                             "salq $16, %0\n"             // do a shift

                             "pcmpistrm $0x00, %2, %7\n"  // generate gap mask in xmm0's first word
                             "pextrw $0, %%xmm0, %%r15\n" // extra data from xmm0's first word
                             "orq %%r15, %0\n"            // save data to "Mask"
                             "salq $16, %0\n"             // do a shift

                             : "=g"(mask)                            //0
                             : "rm"(pNowOutput[0]),                  //1
                               "x"(*(__m128i *)inputPassage),        //2
                               "x"(*(__m128i *)upperMaskList),       //3
                               "x"(*(__m128i *)andMaskList),         //4
                               "x"(*(__m128i *)lowerMaskList),       //5
                               "x"(*(__m128i *)endSentenceMaskList), //6
                               "x"(*(__m128i *)gapMaskList)          //7
                             : "%xmm0", "%r15");
        mask.sentenceBeginMask = ~(mask.gapMask | mask.sentenceMask);
        for (int i = 0; i < 16; i++)
        {
            //putchar(pNowOutput[i]);
        }
        /*putchar('\n');
        printBin(mask.wordMask);
        printBin(mask.sentenceMask);
        printBin(mask.sentenceBeginMask);
        printBin(mask.gapMask);//*/

        //word loop start, get the hash and store it in mem.
        maskCopy = mask;
        flag.cpyLeft = 0; //0 for outside a word, 1 for inside a word
        flag.sentenceShift = 0;
        flag.wordShift = 0;
        flag.sentenceSiginalPosition = __builtin_ctz(maskCopy.sentenceMask | 0xFFF00000);
        //word loop
        register uint32_t shiftOfWord = (uint8_t *)inputPassage - (uint8_t *)memRoot;
        for (uint8_t i = 0; i < 16;)
        {
            while (i > flag.sentenceSiginalPosition)
            {
                wordNumMem[flag.sentenceSiginalPosition] = wordNum;
                maskCopy.sentenceMask >>= flag.sentenceSiginalPosition - flag.sentenceShift + 1;
                flag.sentenceShift = flag.sentenceSiginalPosition + 1;
                flag.sentenceSiginalPosition = flag.sentenceShift + __builtin_ctz(maskCopy.sentenceMask | 0xFFF00000);
            }
            if (flag.wordReadState)
            {
                flag.temp = __builtin_ctz((~maskCopy.wordMask) | 0xFFF00000);
                i = flag.wordShift + flag.temp;
                if (i < 16)
                {
                    //printf("%s i: %d\n", outBuf, i);
                    memcpy(&wordTemp[flag.extractedWordPosition], &pNowOutput[flag.cpyLeft], i - flag.cpyLeft);
                    flag.extractedWordPosition += i - flag.cpyLeft;
                    wordTemp[flag.extractedWordPosition] = 0;
                    uint64_t hashTemp = XXH3_64bits(wordTemp, flag.extractedWordPosition);
                    //printf("\"%s\" 's hash is %llu\n", wordTemp, hashTemp);
                    uint32_t id = hashTemp & 0x03FFFF;
                    //futher hash process
                    if (hashRecord[id] == 0)
                    {
                        hashRecord[id] = (uint32_t)(mem - memRoot);
                        declaremMem(sizeof(struct hashLinkList));
                        pHash = (struct hashLinkList *)(hashRecord[id] + memRoot);
                        pHash->word = (uint32_t)(wordTemp - (char *)memRoot);
                        pHash->hashNum = hashTemp;
                        pHash->next = 0;
                        pHash->n = 1;
                        wordTemp += flag.extractedWordPosition + 1;

                        wordRecord[wordNum++] = (uint8_t *)pHash - (uint8_t *)memRoot;

                        flag.extractedWordPosition = 0;
                        flag.cpyLeft = 0;
                        flag.wordReadState = 0;
                        maskCopy.wordMask >>= flag.temp;
                        flag.wordShift = i;

                        continue;
                    }
                    pHash = (struct hashLinkList *)(hashRecord[id] + memRoot);
                    while (1)
                    {
                        if (likely(pHash->hashNum == hashTemp))
                        {
                            if (likely(Mystrcmp(pHash->word + memRoot, wordTemp, flag.extractedWordPosition) == 0))
                            {
                                pHash->n += 1;
                                wordRecord[wordNum++] = (uint8_t *)pHash - (uint8_t *)memRoot;
                                if (hashTemp == (XXH3_64bits("ter", 3)))
                                {
                                    //fwrite(pNowOutput, 1, 16, stdout);
                                    //putchar('\n');
                                    //fwrite(wordTemp, 1, 3, stdout);
                                    printf("%d sentence\n find ter %d in %p!\n", shiftOfWord + i, pHash->n, pNowOutput);
                                }
                                break;
                            }
                            collitionTime++;
                            //printf("collition between %s %s %x %x!\n",pHash->word + memRoot,wordTemp,pHash->hashNum, hashTemp);
                        }
                        if (pHash->next != 0)
                        {
                            pHash = pHash->next + memRoot;
                            continue;
                        }
                        pHash->next = (uint32_t)(mem - memRoot);
                        pHash = mem;
                        declaremMem(sizeof(struct hashLinkList));
                        pHash->word = (uint32_t)(wordTemp - (char *)memRoot);
                        wordTemp += flag.extractedWordPosition + 1;
                        pHash->n = 1;
                        pHash->hashNum = hashTemp;
                        pHash->next = 0;
                        wordRecord[wordNum++] = (uint8_t *)pHash - (uint8_t *)memRoot;
                        break;
                    }
                    //process end here
                    flag.extractedWordPosition = 0;
                    flag.cpyLeft = 0;
                    flag.wordReadState = 0;
                    maskCopy.wordMask >>= flag.temp;
                    flag.wordShift = i;
                    continue;
                }
                else
                {
                    //putchar('1');
                    memcpy(&wordTemp[flag.extractedWordPosition], &pNowOutput[flag.cpyLeft], 16 - flag.cpyLeft);
                    flag.extractedWordPosition += 16 - flag.cpyLeft;
                    flag.cpyLeft = 0;
                    break;
                }
            }
            else
            {
                flag.temp = __builtin_ctz((uint32_t)maskCopy.wordMask | 0xFFF00000);
                //printf("mask is %x\n", maskCopy.wordMask);
                i = flag.wordShift + flag.temp;
                if (i < 16)
                {
                    flag.cpyLeft = i;
                    flag.wordReadState = 1;
                    maskCopy.wordMask >>= flag.temp;
                    flag.wordShift += flag.temp;
                }
                else
                {
                    break;
                }
            }
        }
        while (16 >= flag.sentenceSiginalPosition)
        {
            wordNumMem[flag.sentenceSiginalPosition] = wordNum;
            maskCopy.sentenceMask >>= flag.sentenceSiginalPosition - flag.sentenceShift + 1;
            flag.sentenceShift = flag.sentenceSiginalPosition + 1;
            flag.sentenceSiginalPosition = flag.sentenceShift + __builtin_ctz(maskCopy.sentenceMask | 0xFFF00000);
        }

        //sentence loop
        flag.sentenceShift = 0;
        for (uint8_t i = 0; i < 16;)
        {
            if (flag.sentenceState)
            {
                flag.temp = __builtin_ctz(mask.sentenceMask | 0xFFF00000);
                i = flag.sentenceShift + flag.temp;
                if (i < 16)
                {
                    //putchar(*(i + (uint8_t *)inputPassage));
                    if (wordNumMem[i] != wordBefore)
                    {
                        sentenceRecord[sentenceNum].wordStart = wordBefore;
                        sentenceRecord[sentenceNum].wordEnd = wordNumMem[i];
                        sentenceRecord[sentenceNum].sentenceBegin = sentenceLeft;
                        sentenceRecord[sentenceNum].sentenceEnd = i + shiftOfWord;
                        sentenceNum++;
                    }
                    wordBefore = wordNumMem[i];
                    //printf("wordNum is %d \n", wordBefore);
                    flag.sentenceState = 0;
                    i++;
                    mask.sentenceMask >>= flag.temp + 1;
                    mask.sentenceBeginMask >>= flag.temp + 1;
                    flag.sentenceShift += flag.temp + 1;
                    continue;
                }
                else
                {
                    break;
                }
            }
            else //outside a sentence
            {
                flag.temp = __builtin_ctz(mask.sentenceBeginMask | 0xFFF00000);
                i = flag.sentenceShift + flag.temp;

                if (i < 16)
                {
                    //printf("%s\n", pNowOutput);
                    //printBin(mask.sentenceBeginMask);
                    //printf("i:%d %c\n", i, *(i + (uint8_t *)inputPassage));
                    sentenceLeft = i + shiftOfWord; //performance
                    mask.sentenceBeginMask >>= flag.temp;
                    mask.sentenceMask >>= flag.temp;
                    flag.sentenceShift += flag.temp;
                    flag.sentenceState = 1;
                }
                else
                {
                    break;
                }
            }
        }
    }
    outBufLength = (uint8_t *)pNowOutput - (uint8_t *)outBuf;
    declaremMem(outBufLength);
}

void processStopWord()
{
    uint32_t lenth = 0;
    for (int i = 0; i < stopWordBufLength; i++)
    {
        while (isalpha(stopWordBuf[i]))
        {
            lenth++;
            i++;
        }
        if (lenth)
        {
            uint64_t hashTemp = XXH3_64bits(&stopWordBuf[i - lenth], lenth);
            uint32_t id = hashTemp & 0x03FFFF;
            if (hashRecord[id] == 0)
            {
                lenth = 0;
                continue;
            }
            pHash = hashRecord[id] + memRoot;
            while (1)
            {
                if (likely(hashTemp == pHash->hashNum))
                {
                    stopWordBuf[i] = 0;
                    //printf("match! 0x%x 0x%x\n", &stopWordBuf[i - lenth], pHash->word + memRoot);
                    if (likely(Mystrcmp((char *)(&stopWordBuf[i - lenth]), pHash->word + (char *)memRoot, lenth) == 0))
                    {
                        pHash->n = 0;
                        //printf("Delete %s\n", pHash->word + memRoot,&stopWordBuf[i +1]);
                        break;
                    }
                }
                if (pHash->next == 0)
                {
                    break;
                }
                pHash = pHash->next + memRoot;
            }
        }
        lenth = 0;
    }
}

int main()
{
    memAligned(16, 0);
    showRunTime();
    FILE *fp;
    fp = fopen("article.txt", "rb");
    passageBuf = mem;
    uint8_t *readNow = passageBuf;
    int inByte = 0;
    while ((inByte = fread(readNow, sizeof(char), 4 * 1024 * 1024, fp)) != 0)
    {
        readNow += inByte;
    }
    passageBufLenth = readNow - passageBuf;
    passageBuf[passageBufLenth] = 0;
    passageBufLenth += 1;
    declaremMem(passageBufLenth);
    memAligned(16, 0);
    fclose(fp);
    fp = fopen("stopwords.txt", "rb");
    stopWordBuf = mem;
    readNow = stopWordBuf;
    inByte = 0;
    while ((inByte = fread(readNow, sizeof(char), 4 * 1024 * 1024, fp)) != 0)
    {
        readNow += inByte;
    }
    stopWordBufLength = readNow - stopWordBuf;
    stopWordBuf[stopWordBufLength] = 0;
    stopWordBufLength += 1;
    declaremMem(stopWordBufLength);
    fclose(fp);
    showRunTime();
    processWord();
    processStopWord();
#if (DEBUG)
    printf("lenthof PassageBuf = %d\n", passageBufLenth);
    printf("lenthof stopWordBuf = %d\n", stopWordBufLength);
    printf("collitionTime = %d\n", collitionTime);
    printf("num of sentence = %d\n", sentenceNum);
    showRunTime();
#endif
    //outputpart start

    for (uint32_t i = 0; i < sentenceNum; i++)
    {
        int tempN = 0;
        for (uint32_t k = sentenceRecord[i].wordStart; k < sentenceRecord[i].wordEnd; k++)
        {
            tempN += ((struct hashLinkList *)(wordRecord[k] + memRoot))->n;
        }
        sentenceN[i].n = tempN;
        sentenceN[i].id = ~i;
        //printf("Sentence %d : %d\n", i + 1, tempN);
    }
    /* //debug
    char debugBuf[1000];
    while (scanf("%s", debugBuf) != EOF)
    {
        printf("The %s has frequence : %d\n", debugBuf, getDebugN(debugBuf));
    }*/

    //ranking: RBTree ranking first 100 element
    int outputN2, outputN;
#if (DEBUG == 0)
    scanf("%d", &outputN2);
#else
    outputN2 = DEBUGN;
#endif
    if (outputN2 < 5)
    {
        outputN = 5;
    }
    else
    {
        outputN = outputN2;
    }
    qsort(sentenceN, outputN, sizeof(long long), cmp);
    uint64_t *sentenceTopRecord = (uint64_t *)&sentenceN[0];
    /*int32_t outputNLargestBit = outputN;
    
    {
        uint8_t movePos = 0;
        while (outputNLargestBit >> movePos != 1)
        {
            movePos++;
        }
        outputNLargestBit = (1 << movePos);
    }
    //see the first k element of sentenceN as a minimal heap; and maintain it, so the first element is the minimal element
    */
    //seem to be useless

    //first get largest 100 num
    // maintain part begin
    for (int i = outputN; i < sentenceNum; i++)
    {
        //printf("%llu vs %llu\n", sentenceTopRecord[i], sentenceTopRecord[0]);
        if (sentenceTopRecord[i] > sentenceTopRecord[0])
        {
            //printf("swap!\n");
            swap(sentenceTopRecord[i], sentenceTopRecord[0]);
            int x = 0;
            while (1)
            {
                int l = 2 * x + 1, r = l + 1;
                if (l >= outputN)
                {
                    break;
                }
                if (r >= outputN)
                {
                    if (sentenceTopRecord[l] < sentenceTopRecord[x])
                    {
                        swap(sentenceTopRecord[l], sentenceTopRecord[x]);
                    }
                    break;
                }
                if (sentenceTopRecord[l] < sentenceTopRecord[x])
                {
                    if (sentenceTopRecord[l] < sentenceTopRecord[r])
                    {
                        swap(sentenceTopRecord[l], sentenceTopRecord[x]);
                        x = l;
                    }
                    else
                    {
                        swap(sentenceTopRecord[r], sentenceTopRecord[x]);
                        x = r;
                    }
                    continue;
                }
                if (sentenceTopRecord[r] < sentenceTopRecord[x])
                {
                    swap(sentenceTopRecord[r], sentenceTopRecord[x]);
                    x = r;
                    continue;
                }
                break;
            }
        }
    }
    // maintain part end

    qsort(sentenceN, outputN, sizeof(long long), cmp);
    showRunTime();

        for (int i = outputN - 1; i > outputN - 1 - 5; i--)
    {
        printf("%d ", sentenceN[i].n);
        /*for (char *j = sentenceRecord[sentenceN[i].id].begin; j <= sentenceRecord[sentenceN[i].id].end; j++)
        {
            putchar(*j);
        }*/
        int id = ~sentenceN[i].id;
        fwrite(sentenceRecord[id].sentenceBegin + memRoot, sizeof(char), sentenceRecord[id].sentenceEnd - sentenceRecord[id].sentenceBegin + 1, stdout);
        putchar('\n');
    }

    int air = 0;
    if (outputN > sentenceNum)
    {
        air = outputN - sentenceNum;
    }
#if (DEBUG)
    freopen("lowerArticle.txt", "wb", stdout);
    for (int i = outputN - 1; i >= 0; i--)
    {
        int id = ~sentenceN[i].id;
        printf("%d %d ", sentenceN[i].n, sentenceRecord[id].wordEnd - sentenceRecord[id].wordStart);
        /*for (char *j = sentenceRecord[sentenceN[i].id].begin; j <= sentenceRecord[sentenceN[i].id].end; j++)
        {
            putchar(*j);
        }*/
        fwrite(sentenceRecord[id].sentenceBegin + memRoot, sizeof(char), sentenceRecord[id].sentenceEnd - sentenceRecord[id].sentenceBegin + 1, stdout);
        putchar('\n');
        for (uint32_t k = sentenceRecord[id].wordStart; k < sentenceRecord[id].wordEnd; k++)
        {
            printf("%s:%d ", (((struct hashLinkList *)(wordRecord[k] + memRoot))->word + memRoot), (((struct hashLinkList *)(wordRecord[k] + memRoot))->n));
        }
        putchar('\n');
    }
#else
    freopen("results.txt", "wb", stdout);
    for (int i = outputN - 1; i >= air; i--)
    {
        int id = ~sentenceN[i].id;
        printf("%d ", sentenceN[i].n);
        /*for (char *j = sentenceRecord[sentenceN[i].id].begin; j <= sentenceRecord[sentenceN[i].id].end; j++)
        {
            putchar(*j);
        }*/
        fwrite(sentenceRecord[id].sentenceBegin + memRoot, sizeof(char), sentenceRecord[id].sentenceEnd - sentenceRecord[id].sentenceBegin + 1, stdout);
        putchar('\n');
    }
#endif
    for (int i = 0; i < air; i++)
    {
        putchar('0');
        putchar('\n');
    }
    return 0;

    showRunTime();
}
