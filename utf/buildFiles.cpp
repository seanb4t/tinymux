#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <string.h>

#include "ConvertUTF.h"
#include "smutil.h"

const bool mux_isdigit[256] =
{
//  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
//
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 1
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 2
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,  // 3
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 5
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 6
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 7

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 8
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 9
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // A
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // B
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // C
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // D
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // E
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0   // F
};

const bool mux_isspace[256] =
{
//  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
//
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,  // 0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 1
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 2
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 3
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 5
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 6
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 7

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 8
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 9
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // A
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // B
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // C
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // D
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // E
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0   // F
};

#define mux_isdigit(x) (mux_isdigit[(unsigned char)(x)])
#define mux_isspace(x) (mux_isspace[(unsigned char)(x)])

const char TableATOI[16][10] =
{
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9},
    { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
    { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
    { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
    { 40, 41, 42, 43, 44, 45, 46, 47, 48, 49},
    { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
    { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
    { 70, 71, 72, 73, 74, 75, 76, 77, 78, 79},
    { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
    { 90, 91, 92, 93, 94, 95, 96, 97, 98, 99}
};

long mux_atol(const char *pString)
{
    long sum = 0;
    int LeadingCharacter = 0;

    // Convert ASCII digits
    //
    unsigned int c1;
    unsigned int c0 = pString[0];
    if (!mux_isdigit(c0))
    {
        while (mux_isspace(pString[0]))
        {
            pString++;
        }
        LeadingCharacter = pString[0];
        if (  LeadingCharacter == '-'
           || LeadingCharacter == '+')
        {
            pString++;
        }
        c0 = pString[0];
        if (!mux_isdigit(c0))
        {
            return 0;
        }
    }

    do
    {
        c1 = pString[1];
        if (mux_isdigit(c1))
        {
            sum = 100 * sum + TableATOI[c0-'0'][c1-'0'];
            pString += 2;
        }
        else
        {
            sum = 10 * sum + (c0-'0');
            break;
        }
    } while (mux_isdigit(c0 = pString[0]));

    // Interpret sign
    //
    if (LeadingCharacter == '-')
    {
        sum = -sum;
    }
    return sum;
}

// Korean Hangul Constants.
//
const UTF32 SBase = 0xAC00;
const UTF32 LBase = 0x1100;
const UTF32 VBase = 0x1161;
const UTF32 TBase = 0x11A7;
const UTF32 SCount = 11172;
const int LCount = 19;
const int VCount = 21;
const int TCount = 28;
const int NCount = VCount * TCount;

const size_t codepoints = 1114109;

#define CATEGORY_LETTER               0x0001000
#define SUBCATEGORY_UPPER             0x0000001   // Lu
#define SUBCATEGORY_LOWER             0x0000002   // Ll
#define SUBCATEGORY_TITLE             0x0000004   // Lt
#define SUBCATEGORY_LET_MODIFIER      0x0000008   // Lm
#define SUBCATEGORY_LET_OTHER         0x0000010   // Lo

#define CATEGORY_MARK                 0x0002000
#define SUBCATEGORY_NONSPACING        0x0000001   // Mn
#define SUBCATEGORY_SPACING_COMBINING 0x0000002   // Mc
#define SUBCATEGORY_SPACING_ENCLOSING 0x0000004   // Me

#define CATEGORY_NUMBER               0x0004000
#define SUBCATEGORY_DECIMAL_DIGIT     0x0000001   // Nd
#define SUBCATEGORY_LETTER            0x0000002   // Nl
#define SUBCATEGORY_NUM_OTHER         0x0000004   // No

#define CATEGORY_PUNCTUATION          0x0008000
#define SUBCATEGORY_CONNECTOR         0x0000001   // Pc
#define SUBCATEGORY_DASH              0x0000002   // Pd
#define SUBCATEGORY_OPEN              0x0000004   // Ps
#define SUBCATEGORY_CLOSE             0x0000008   // Pe
#define SUBCATEGORY_INITIAL_QUOTE     0x0000010   // Pi
#define SUBCATEGORY_FINAL_QUOTE       0x0000020   // Pf
#define SUBCATEGORY_PUNC_OTHER        0x0000040   // Po

#define CATEGORY_SYMBOL               0x0010000
#define SUBCATEGORY_MATH              0x0000001   // Sm
#define SUBCATEGORY_CURRENCY          0x0000002   // Sc
#define SUBCATEGORY_SYM_MODIFIER      0x0000004   // Sk
#define SUBCATEGORY_SYM_OTHER         0x0000008   // So

#define CATEGORY_SEPARATOR            0x0020000
#define SUBCATEGORY_SPACE             0x0000001   // Zs
#define SUBCATEGORY_LINE              0x0000002   // Zl
#define SUBCATEGORY_PARAGRAPH         0x0000004   // Zp

#define CATEGORY_OTHER                0x0040000
#define SUBCATEGORY_CONTROL           0x0000001   // Cc
#define SUBCATEGORY_FORMAT            0x0000002   // Cf
#define SUBCATEGORY_SURROGATE         0x0000004   // Cs
#define SUBCATEGORY_PRIVATE_USE       0x0000008   // Co
#define SUBCATEGORY_NOT_ASSIGNED      0x0000010   // Cn

static struct
{
    int   cat;
    char *catlet;
} CategoryTable[] =
{
    { CATEGORY_LETTER|SUBCATEGORY_UPPER,              "Lu" },
    { CATEGORY_LETTER|SUBCATEGORY_LOWER,              "Ll" },
    { CATEGORY_LETTER|SUBCATEGORY_TITLE,              "Lt" },
    { CATEGORY_LETTER|SUBCATEGORY_LET_MODIFIER,       "Lm" },
    { CATEGORY_LETTER|SUBCATEGORY_LET_OTHER,          "Lo" },
    { CATEGORY_MARK|SUBCATEGORY_NONSPACING,           "Mn" },
    { CATEGORY_MARK|SUBCATEGORY_SPACING_COMBINING,    "Mc" },
    { CATEGORY_MARK|SUBCATEGORY_SPACING_ENCLOSING,    "Me" },
    { CATEGORY_NUMBER|SUBCATEGORY_DECIMAL_DIGIT,      "Nd" },
    { CATEGORY_NUMBER|SUBCATEGORY_LETTER,             "Nl" },
    { CATEGORY_NUMBER|SUBCATEGORY_NUM_OTHER,          "No" },
    { CATEGORY_PUNCTUATION|SUBCATEGORY_CONNECTOR,     "Pc" },
    { CATEGORY_PUNCTUATION|SUBCATEGORY_DASH,          "Pd" },
    { CATEGORY_PUNCTUATION|SUBCATEGORY_OPEN,          "Ps" },
    { CATEGORY_PUNCTUATION|SUBCATEGORY_CLOSE,         "Pe" },
    { CATEGORY_PUNCTUATION|SUBCATEGORY_INITIAL_QUOTE, "Pi" },
    { CATEGORY_PUNCTUATION|SUBCATEGORY_FINAL_QUOTE,   "Pf" },
    { CATEGORY_PUNCTUATION|SUBCATEGORY_PUNC_OTHER,    "Po" },
    { CATEGORY_SYMBOL|SUBCATEGORY_MATH,               "Sm" },
    { CATEGORY_SYMBOL|SUBCATEGORY_CURRENCY,           "Sc" },
    { CATEGORY_SYMBOL|SUBCATEGORY_SYM_MODIFIER,       "Sk" },
    { CATEGORY_SYMBOL|SUBCATEGORY_SYM_OTHER,          "So" },
    { CATEGORY_SEPARATOR|SUBCATEGORY_SPACE,           "Zs" },
    { CATEGORY_SEPARATOR|SUBCATEGORY_LINE,            "Zl" },
    { CATEGORY_SEPARATOR|SUBCATEGORY_PARAGRAPH,       "Zp" },
    { CATEGORY_OTHER|SUBCATEGORY_CONTROL,             "Cc" },
    { CATEGORY_OTHER|SUBCATEGORY_FORMAT,              "Cf" },
    { CATEGORY_OTHER|SUBCATEGORY_SURROGATE,           "Cs" },
    { CATEGORY_OTHER|SUBCATEGORY_PRIVATE_USE,         "Co" },
    { 0, NULL }
};

#define BIDI_LEFT_TO_RIGHT               1
#define BIDI_LEFT_TO_RIGHT_EMBEDDING     2
#define BIDI_LEFT_TO_RIGHT_OVERRIDE      3
#define BIDI_RIGHT_TO_LEFT               4
#define BIDI_RIGHT_TO_LEFT_ARABIC        5
#define BIDI_RIGHT_TO_LEFT_EMBEDDING     6
#define BIDI_RIGHT_TO_LEFT_OVERRIDE      7
#define BIDI_POP_DIRECTIONAL_FORMAT      8
#define BIDI_EUROPEAN_NUMBER             9
#define BIDI_EUROPEAN_NUMBER_SEPARATOR  10
#define BIDI_EUROPEAN_NUMBER_TERMINATOR 11
#define BIDI_ARABIC_NUMBER              12
#define BIDI_COMMON_NUMBER_SEPARATOR    13
#define BIDI_NON_SPACING_MARK           14
#define BIDI_BOUNDARY_NEUTRAL           15
#define BIDI_PARAGRAPH_SEPARATOR        16
#define BIDI_SEGMENT_SEPARATOR          17
#define BIDI_WHITESPACE                 18
#define BIDI_OTHER_NEUTRALS             19

static struct
{
    int   BiDi;
    char *BiDiLet;
} BiDiTable[] =
{
    { BIDI_LEFT_TO_RIGHT,              "L"   },
    { BIDI_LEFT_TO_RIGHT_EMBEDDING,    "LRE" },
    { BIDI_LEFT_TO_RIGHT_OVERRIDE,     "LRO" },
    { BIDI_RIGHT_TO_LEFT,              "R"   },
    { BIDI_RIGHT_TO_LEFT_ARABIC,       "AL"  },
    { BIDI_RIGHT_TO_LEFT_EMBEDDING,    "RLE" },
    { BIDI_RIGHT_TO_LEFT_OVERRIDE,     "RLO" },
    { BIDI_POP_DIRECTIONAL_FORMAT,     "PDF" },
    { BIDI_EUROPEAN_NUMBER,            "EN"  },
    { BIDI_EUROPEAN_NUMBER_SEPARATOR,  "ES"  },
    { BIDI_EUROPEAN_NUMBER_TERMINATOR, "ET"  },
    { BIDI_ARABIC_NUMBER,              "AN"  },
    { BIDI_COMMON_NUMBER_SEPARATOR,    "CS"  },
    { BIDI_NON_SPACING_MARK,           "NSM" },
    { BIDI_BOUNDARY_NEUTRAL,           "BN"  },
    { BIDI_PARAGRAPH_SEPARATOR,        "B"   },
    { BIDI_SEGMENT_SEPARATOR,          "S"   },
    { BIDI_WHITESPACE,                 "WS"  },
    { BIDI_OTHER_NEUTRALS,             "ON"  },
    { 0, NULL }
};

#define DECOMP_TYPE_NONE               0
#define DECOMP_TYPE_FONT               1
#define DECOMP_TYPE_NOBREAK            2
#define DECOMP_TYPE_INITIAL            3
#define DECOMP_TYPE_MEDIAL             4
#define DECOMP_TYPE_FINAL              5
#define DECOMP_TYPE_ISOLATED           6
#define DECOMP_TYPE_CIRCLE             7
#define DECOMP_TYPE_SUPER              8
#define DECOMP_TYPE_SUB                9
#define DECOMP_TYPE_VERTICAL          10
#define DECOMP_TYPE_WIDE              11
#define DECOMP_TYPE_NARROW            12
#define DECOMP_TYPE_SMALL             13
#define DECOMP_TYPE_SQUARE            14
#define DECOMP_TYPE_FRACTION          15
#define DECOMP_TYPE_COMPAT            16

static struct
{
    int   DecompType;
    char *DecompTypeLet;
} DecompTypeTable[] =
{
    { DECOMP_TYPE_FONT,                "font"     },
    { DECOMP_TYPE_NOBREAK,             "noBreak"  },
    { DECOMP_TYPE_INITIAL,             "initial"  },
    { DECOMP_TYPE_MEDIAL,              "medial"   },
    { DECOMP_TYPE_FINAL,               "final"    },
    { DECOMP_TYPE_ISOLATED,            "isolated" },
    { DECOMP_TYPE_CIRCLE,              "circle"   },
    { DECOMP_TYPE_SUPER,               "super"    },
    { DECOMP_TYPE_SUB,                 "sub"      },
    { DECOMP_TYPE_VERTICAL,            "vertical" },
    { DECOMP_TYPE_WIDE,                "wide"     },
    { DECOMP_TYPE_NARROW,              "narrow"   },
    { DECOMP_TYPE_SMALL,               "small"    },
    { DECOMP_TYPE_SQUARE,              "square"   },
    { DECOMP_TYPE_FRACTION,            "fraction" },
    { DECOMP_TYPE_COMPAT,              "compat"   },
    { 0, NULL }
};

class CodePoint
{
public:
    CodePoint();
    ~CodePoint();

    bool IsDefined(void) { return m_bDefined; };

    void SetDescription(char *pDescription);
    char *GetDescription(void) { return m_pDescription; };

    void SetCategory(int category) { m_category = category; };
    int  GetCategory(void) { return m_category; };
    char *GetCategoryName(void);

    void SetCombiningClass(int cc) { m_class = cc; };
    int  GetCombiningClass(void) { return m_class; };

    void SetBiDi(int bidi) { m_bidi = bidi; };
    int  GetBiDi(void) { return m_bidi; };
    char *GetBiDiName(void);

    void SetDecompositionType(int dt) { m_DecompType = dt; };
    int  GetDecompositionType(void) { return m_DecompType; };
    char *GetDecompositionTypeName(void);

    void SetDecompositionMapping(int nPoints, UTF32 pts[]);
    int GetDecompositionMapping(UTF32 pts[]);

    void SetDecimalDigitValue(int n);
    bool GetDecimalDigitValue(int *pn);

    void SetDigitValue(int n);
    bool GetDigitValue(int *pn);

    void SetNumericValue(char *p);
    bool GetNumericValue(char **p);

    void SetBidiMirrored(bool b) { m_bBidiMirrored = b; };
    bool GetBidiMirrored(void) { return m_bBidiMirrored; };

    void SetUnicode1Name(char *p);
    char *GetUnicode1Name(void) { return m_pUnicode1Name; };

    void SetISOComment(char *p);
    char *GetISOComment(void) { return m_pISOComment; };

    void SetSimpleUppercaseMapping(UTF32 ptUpper) { m_SimpleUppercaseMapping = ptUpper; };
    void SetSimpleLowercaseMapping(UTF32 ptLower) { m_SimpleLowercaseMapping = ptLower; };
    void SetSimpleTitlecaseMapping(UTF32 ptTitle) { m_SimpleTitlecaseMapping = ptTitle; };

    UTF32 GetSimpleUppercaseMapping(void) { return m_SimpleUppercaseMapping; };
    UTF32 GetSimpleLowercaseMapping(void) { return m_SimpleLowercaseMapping; };
    UTF32 GetSimpleTitlecaseMapping(void) { return m_SimpleTitlecaseMapping; };

    void SetProhibited(void) { m_bProhibited = true; };
    bool IsProhibited(void) { return m_bProhibited; };

private:
    bool  m_bDefined;
    char *m_pDescription;
    int   m_category;
    int   m_class;
    int   m_bidi;
    int   m_DecompType;
    int   m_nDecompMapping;
    UTF32 m_aDecompMapping[30];

    int   m_nDecimalDigitValue;
    bool  m_bHaveDecimalDigitValue;
    int   m_nDigitValue;
    bool  m_bHaveDigitValue;
    char *m_pNumericValue;
    bool  m_bHaveNumericValue;

    bool  m_bBidiMirrored;
    char *m_pUnicode1Name;
    char *m_pISOComment;
    UTF32 m_SimpleUppercaseMapping;
    UTF32 m_SimpleLowercaseMapping;
    UTF32 m_SimpleTitlecaseMapping;

    bool  m_bProhibited;
};

void CodePoint::SetDecimalDigitValue(int n)
{
    m_nDecimalDigitValue = n;
    m_bHaveDecimalDigitValue = true;
}

bool CodePoint::GetDecimalDigitValue(int *pn)
{
    *pn = m_nDecimalDigitValue;
    return m_bHaveDecimalDigitValue;
}

void CodePoint::SetDigitValue(int n)
{
    m_nDigitValue = n;
    m_bHaveDigitValue = true;
}

bool CodePoint::GetDigitValue(int *pn)
{
    *pn = m_nDigitValue;
    return m_bHaveDigitValue;
}

void CodePoint::SetNumericValue(char *p)
{
    size_t n = strlen(p);
    m_pNumericValue = new char[n+1];
    memcpy(m_pNumericValue, p, n+1);
    m_bHaveNumericValue = true;
}

bool CodePoint::GetNumericValue(char **p)
{
    *p = m_pNumericValue;
    return m_bHaveNumericValue;
}

int CodePoint::GetDecompositionMapping(UTF32 pts[])
{
    for (int i = 0; i < m_nDecompMapping; i++)
    {
        pts[i] = m_aDecompMapping[i];
    }
    return m_nDecompMapping;
}

void CodePoint::SetDecompositionMapping(int nPoints, UTF32 pts[])
{
    m_nDecompMapping = nPoints;
    for (int i = 0; i < nPoints; i++)
    {
        m_aDecompMapping[i] = pts[i];
    }
}

CodePoint::CodePoint()
{
    m_bDefined = false;
    m_pDescription = NULL;
    m_category = CATEGORY_OTHER|SUBCATEGORY_NOT_ASSIGNED;
    m_class = 0;
    m_bidi = BIDI_LEFT_TO_RIGHT; // BUG: The default is not the same for all code point values.
    m_DecompType = DECOMP_TYPE_NONE;
    m_nDecompMapping = 0;
    m_nDecimalDigitValue = 0;
    m_bHaveDecimalDigitValue = false;
    m_nDigitValue = 0;
    m_bHaveDigitValue = false;
    m_pNumericValue = NULL;
    m_bHaveNumericValue = false;
    m_bBidiMirrored = false;
    m_pUnicode1Name = NULL;
    m_pISOComment = NULL;
    m_SimpleUppercaseMapping = UNI_EOF;
    m_SimpleLowercaseMapping = UNI_EOF;
    m_SimpleTitlecaseMapping = UNI_EOF;
    m_bProhibited = false;
}

CodePoint::~CodePoint()
{
    if (NULL != m_pDescription)
    {
        delete [] m_pDescription;
        m_pDescription = NULL;
    }
    m_bDefined = false;
}

void CodePoint::SetDescription(char *pDescription)
{
    if (NULL != m_pDescription)
    {
        delete [] m_pDescription;
        m_pDescription = NULL;
    }
    size_t n = strlen(pDescription);
    m_pDescription = new char[n+1];
    memcpy(m_pDescription, pDescription, n+1);
    m_bDefined = true;
}

void CodePoint::SetUnicode1Name(char *p)
{
    if (NULL != m_pUnicode1Name)
    {
        delete [] m_pUnicode1Name;
        m_pUnicode1Name = NULL;
    }
    size_t n = strlen(p);
    m_pUnicode1Name = new char[n+1];
    memcpy(m_pUnicode1Name, p, n+1);
}

void CodePoint::SetISOComment(char *p)
{
    if (NULL != m_pISOComment)
    {
        delete [] m_pISOComment;
        m_pISOComment = NULL;
    }
    size_t n = strlen(p);
    m_pISOComment = new char[n+1];
    memcpy(m_pISOComment, p, n+1);
}

class UniData
{
public:
    UniData() {};
    ~UniData() {};

    void LoadUnicodeDataFile(void);
    void LoadUnicodeDataLine(UTF32 codepoint, int nFields, char *aFields[]);
    void LoadUnicodeHanFile(void);

    void Prohibit(void);

    void SaveMasterFile(void);
    void SaveTranslateToUpper(void);
    void SaveTranslateToLower(void);
    void SaveTranslateToTitle(void);
    void SaveClassifyPrivateUse(void);
    void SaveDecompositions(void);
    void SaveClassifyPrintable(void);

    void GetDecomposition(UTF32 pt, int dt, int &nPoints, UTF32 pts[]);

private:
    CodePoint cp[codepoints+1];
};

UniData *g_UniData = NULL;

void UniData::GetDecomposition(UTF32 pt, int dt, int &nPoints, UTF32 pts[])
{
    if (!cp[pt].IsDefined())
    {
        exit(0);
    }

    if (  DECOMP_TYPE_NONE != cp[pt].GetDecompositionType()
       && dt != cp[pt].GetDecompositionType())
    {
        pts[nPoints++] = pt;
        return;
    }

    UTF32 pts2[50];
    int n = cp[pt].GetDecompositionMapping(pts2);
    if (n == 1 && pts2[0] == pt)
    {
        pts[nPoints++] = pt;
        return;
    }

    for (UTF32 i = 0; i < n; i++)
    {
        GetDecomposition(pts2[i], dt, nPoints, pts);
    }
}

int main(int argc, char *argv[])
{
    if (1 != argc)
    {
        printf("Usage: buildFiles uses UnicodeData.txt\n");
        return 0;
    }

    g_UniData = new UniData;
    g_UniData->LoadUnicodeDataFile();
    g_UniData->LoadUnicodeHanFile();

    g_UniData->Prohibit();

    g_UniData->SaveMasterFile();
    g_UniData->SaveTranslateToUpper();
    g_UniData->SaveTranslateToLower();
    g_UniData->SaveTranslateToTitle();
    g_UniData->SaveClassifyPrivateUse();
    g_UniData->SaveDecompositions();
    g_UniData->SaveClassifyPrintable();

    return 0;
}

void UniData::LoadUnicodeDataFile(void)
{
    FILE *fp = fopen("UnicodeData.txt", "r");
    if (NULL != fp)
    {
        char buffer1[1024];
        char buffer2[1024];
        while (NULL != ReadLine(fp, buffer1, sizeof(buffer1)))
        {
            bool  bRange = false;
            bool  bRangeValid = false;

            int   nFields1, nFields2;
            char *aFields1[15], *aFields2[15];

            ParseFields(buffer1, 15, nFields1, aFields1);
            if (  2 <= nFields1
               && aFields1[1][0] == '<')
            {
                size_t n1 = strlen(aFields1[1]);
                if (  9 <= n1
                   && strcmp(&aFields1[1][n1-8], ", First>") == 0)
                {
                    bRange = true;
                    if (NULL != ReadLine(fp, buffer2, sizeof(buffer2)))
                    {
                        ParseFields(buffer2, 15, nFields2, aFields2);
                        if (  2 <= nFields2
                           && aFields2[1][0] == '<')
                        {
                            size_t n2 = strlen(aFields2[1]);
                            if (  8 <= n2
                               && strcmp(&aFields2[1][n2-7], ", Last>") == 0)
                            {
                                aFields1[1][n1-8] = '\0';
                                aFields1[1]++;
                                aFields2[1][n2-7] = '\0';
                                aFields2[1]++;

                                bRangeValid = true;
                            }
                        }
                    }
                }
            }

            if (!bRange)
            {
                // Single Code Point.
                //
                UTF32 pt = DecodeCodePoint(aFields1[0]);
                LoadUnicodeDataLine(pt, nFields1, aFields1);
            }
            else if (bRangeValid)
            {
                // Range of Code Points.
                //
                bool bMatches = false;
                if (nFields1 == nFields2)
                {
                    bMatches = true;
                    for (int i = 1; i < nFields1; i++)
                    {
                        if (strcmp(aFields1[i], aFields2[i]) != 0)
                        {
                            bMatches = false;
                        }
                    }
                }

                if (bMatches)
                {
                    //printf("%s - %s\n", aFields1[0], aFields2[0]);
                    UTF32 pt1 = DecodeCodePoint(aFields1[0]);
                    UTF32 pt2 = DecodeCodePoint(aFields2[0]);
                    if (pt1 != SBase)
                    {
                        // non-Hangul range.
                        //
                        for (UTF32 pt = pt1; pt <= pt2; pt++)
                        {
                            LoadUnicodeDataLine(pt, nFields1, aFields1);
                        }
                    }
                    else
                    {
                        // Korean Hangul range.
                        //
                        for (UTF32 pt = pt1; pt <= pt2; pt++)
                        {
                            UTF32 SIndex = pt - SBase;
                            UTF32 L = LBase + SIndex / NCount;
                            UTF32 V = VBase + (SIndex % NCount) / TCount;
                            UTF32 T = TBase + SIndex % TCount;

                            char Hangul[1024];
                            if (T == TBase)
                            {
                                sprintf(Hangul, "%04X %04X", L, V);
                            }
                            else
                            {
                                sprintf(Hangul, "%04X %04X %04X", L, V, T);
                            }
                            aFields1[5] = Hangul;
                            LoadUnicodeDataLine(pt, nFields1, aFields1);
                        }
                    }
                }
                else
                {
                    printf("***ERROR: %s in range form does not agree with %s\n", aFields1[0], aFields2[0]);
                }
            }
            else
            {
                printf("***ERROR: Invalid Range form near %s\n", aFields1[0]);
            }
        }
        fclose(fp);
    }
}

void UniData::LoadUnicodeDataLine(UTF32 codepoint, int nFields, char *aFields[])
{
    if (codepoint <= codepoints)
    {
        // Description
        //
        if (2 <= nFields)
        {
            cp[codepoint].SetDescription(aFields[1]);
        }

        // Category
        //
        if (3 <= nFields)
        {
            bool bValid = false;
            int i = 0;
            while (CategoryTable[i].catlet)
            {
                if (strcmp(aFields[2], CategoryTable[i].catlet) == 0)
                {
                    cp[codepoint].SetCategory(CategoryTable[i].cat);
                    bValid = true;
                    break;
                }
                i++;
            }

            if (!bValid)
            {
                printf("***ERROR: Invalid Category %s for U+%04X\n", aFields[2], codepoint);
                exit(0);
            }
        }

        // Combining Class.
        //
        if (4 <= nFields)
        {
            int cc = mux_atol(aFields[3]);
            cp[codepoint].SetCombiningClass(cc);
        }

        // Bidi algorithm.
        //
        if (5 <= nFields)
        {
            bool bValid = false;
            int i = 0;
            while (BiDiTable[i].BiDiLet)
            {
                if (strcmp(aFields[4], BiDiTable[i].BiDiLet) == 0)
                {
                    cp[codepoint].SetBiDi(BiDiTable[i].BiDi);
                    bValid = true;
                    break;
                }
                i++;
            }

            if (!bValid)
            {
                printf("***ERROR: Invalid BiDi %s for U+%04X\n", aFields[4], codepoint);
                exit(0);
            }
        }

        // Decomposition Type and Mapping.
        //
        if (6 <= nFields)
        {
            bool bValid = false;
            char *pDecomposition_Mapping = NULL;
            char *pDecomposition_Type = NULL;
            if ('<' == aFields[5][0])
            {
               char *p = strchr(aFields[5]+1, '>');
               if (NULL != p)
               {
                   *p++ = '\0';
                   while (mux_isspace(*p))
                   {
                       p++;
                   }
                   pDecomposition_Type = aFields[5]+1;
                   pDecomposition_Mapping = p;
                   bValid = true;
               }
            }
            else
            {
                pDecomposition_Type = "";
                pDecomposition_Mapping = aFields[5];
                bValid = true;
            }

            if (bValid)
            {
                if ('\0' != pDecomposition_Type[0])
                {
                    bValid = false;
                    int i = 0;
                    while (DecompTypeTable[i].DecompType)
                    {
                        if (strcmp(pDecomposition_Type, DecompTypeTable[i].DecompTypeLet) == 0)
                        {
                            cp[codepoint].SetDecompositionType(DecompTypeTable[i].DecompType);
                            bValid = true;
                            break;
                        }
                        i++;
                    }
                }

                if (!bValid)
                {
                    printf("***ERROR: Decomposition Type Name not found (%s).\n", pDecomposition_Type);
                }
                else
                {
                    int   nPoints;
                    char *aPoints[30];
                    UTF32 pts[30];
                    ParsePoints(pDecomposition_Mapping, 30, nPoints, aPoints);
                    for (int i = 0; i < nPoints; i++)
                    {
                        pts[i] = DecodeCodePoint(aPoints[i]);
                    }

                    if (0 == nPoints)
                    {
                        pts[0] = codepoint;
                        nPoints = 1;
                    }

                    cp[codepoint].SetDecompositionMapping(nPoints, pts);
                }
            }
            else
            {
                printf("***ERROR: Expression malformed.\n");
            }

            if (!bValid)
            {
                printf("***ERROR: Invalid Decomposition Type, '%s', or Mapping, '%s', for U+%04X\n", pDecomposition_Type, pDecomposition_Mapping, codepoint);
                exit(0);
            }
        }

        // Decimal Digit Value.
        //
        if (  7 <= nFields
           && '\0' != aFields[6][0])
        {
            int cc = mux_atol(aFields[6]);
            cp[codepoint].SetDecimalDigitValue(cc);
        }

        // Digit Value.
        //
        if (  8 <= nFields
           && '\0' != aFields[7][0])
        {
            int cc = mux_atol(aFields[7]);
            cp[codepoint].SetDigitValue(cc);
        }

        // Numeric Value.
        //
        if (  9 <= nFields
           && '\0' != aFields[8][0])
        {
            cp[codepoint].SetNumericValue(aFields[8]);
        }

        // Bidi_Mirrored.
        //
        if (  10 <= nFields
           && '\0' != aFields[9][0])
        {
            if ('Y' == aFields[9][0])
            {
                cp[codepoint].SetBidiMirrored(true);
            }
            else if ('N' == aFields[9][0])
            {
                cp[codepoint].SetBidiMirrored(false);
            }
            else
            {
                printf("Bidi_Mirrored '%s'.\n", aFields[9]);
                exit(0);
            }
        }

        // Unicode_1_Name.
        //
        if (  11 <= nFields
           && '\0' != aFields[10][0])
        {
            cp[codepoint].SetUnicode1Name(aFields[10]);
        }

        // ISO Comment.
        //
        if (  12 <= nFields
           && '\0' != aFields[11][0])
        {
            cp[codepoint].SetISOComment(aFields[11]);
        }

        // Simple Uppercase Mapping.
        //
        if (  13 <= nFields
           && '\0' != aFields[12][0])
        {
            UTF32 pt = DecodeCodePoint(aFields[12]);
            cp[codepoint].SetSimpleUppercaseMapping(pt);
        }

        // Simple Lowercase Mapping.
        //
        if (  14 <= nFields
           && '\0' != aFields[13][0])
        {
            UTF32 pt = DecodeCodePoint(aFields[13]);
            cp[codepoint].SetSimpleLowercaseMapping(pt);
        }

        // Simple Titlecase Mapping.
        //
        if (  15 <= nFields
           && '\0' != aFields[14][0])
        {
            UTF32 pt = DecodeCodePoint(aFields[14]);
            cp[codepoint].SetSimpleTitlecaseMapping(pt);
        }
    }
}

void UniData::SaveDecompositions()
{
    FILE *fp = fopen("Decompositions.txt", "w+");
    if (NULL == fp)
    {
        return;
    }

    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (cp[pt].IsDefined())
        {
            int   nPoints = 0;
            UTF32 pts[100];
            GetDecomposition(pt, DECOMP_TYPE_NONE, nPoints, pts);

            if (nPoints != 1 || pts[0] != pt)
            {
                fprintf(fp, "%04X;", pt);
                for (UTF32 pt2 = 0; pt2 < nPoints; pt2++)
                {
                    if (pt2 != 0)
                    {
                        fprintf(fp, " ");
                    }
                    fprintf(fp, "%04X", pts[pt2]);
                }
                fprintf(fp, ";%s\n", cp[pt].GetDescription());
            }
        }
    }
    fclose(fp);
}

void UniData::SaveTranslateToUpper()
{
    FILE *fp = fopen("tr_toupper.txt", "w+");
    if (NULL == fp)
    {
        return;
    }

    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (  cp[pt].IsDefined()
           && !cp[pt].IsProhibited())
        {
            UTF32 ptUpper = cp[pt].GetSimpleUppercaseMapping();
            if (  UNI_EOF != ptUpper
               && cp[ptUpper].IsDefined()
               && !cp[ptUpper].IsProhibited())
            {
                char *p = cp[pt].GetUnicode1Name();
                fprintf(fp, "%04X;%04X;%s;%s\n", pt, ptUpper, cp[pt].GetDescription(), (NULL == p) ? "" : p);
            }
        }
    }
    fclose(fp);
}

void UniData::SaveTranslateToLower()
{
    FILE *fp = fopen("tr_tolower.txt", "w+");
    if (NULL == fp)
    {
        return;
    }

    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (  cp[pt].IsDefined()
           && !cp[pt].IsProhibited())
        {
            UTF32 ptLower = cp[pt].GetSimpleLowercaseMapping();
            if (  UNI_EOF != ptLower
               && cp[ptLower].IsDefined()
               && !cp[ptLower].IsProhibited())
            {
                char *p = cp[pt].GetUnicode1Name();
                fprintf(fp, "%04X;%04X;%s;%s\n", pt, ptLower, cp[pt].GetDescription(), (NULL == p) ? "" : p);
            }
        }
    }
    fclose(fp);
}

void UniData::SaveTranslateToTitle()
{
    FILE *fp = fopen("tr_totitle.txt", "w+");
    if (NULL == fp)
    {
        return;
    }

    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (  cp[pt].IsDefined()
           && !cp[pt].IsProhibited())
        {
            UTF32 ptTitle = cp[pt].GetSimpleTitlecaseMapping();
            if (  UNI_EOF != ptTitle
               && cp[ptTitle].IsDefined()
               && !cp[ptTitle].IsProhibited())
            {
                char *p = cp[pt].GetUnicode1Name();
                fprintf(fp, "%04X;%04X;%s;%s\n", pt, ptTitle, cp[pt].GetDescription(), (NULL == p) ? "" : p);
            }
        }
    }
    fclose(fp);
}

void UniData::SaveMasterFile(void)
{
    FILE *fp = fopen("UnicodeMaster.txt", "w+");
    if (NULL == fp)
    {
        return;
    }

    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (cp[pt].IsDefined())
        {
            fprintf(fp, "%04X;%s;%s;%d;%s", pt, cp[pt].GetDescription(), cp[pt].GetCategoryName(),
                cp[pt].GetCombiningClass(), cp[pt].GetBiDiName());

            char DecompBuffer[1024];
            DecompBuffer[0] = '\0';

            if (cp[pt].GetDecompositionType() != DECOMP_TYPE_NONE)
            {
                strcat(DecompBuffer, "<");
                strcat(DecompBuffer, cp[pt].GetDecompositionTypeName());
                strcat(DecompBuffer, ">");
            }

            UTF32 pts[30];
            int nPoints = cp[pt].GetDecompositionMapping(pts);

            if (nPoints != 1 || pts[0] != pt)
            {
                if ('\0' != DecompBuffer[0])
                {
                    strcat(DecompBuffer, " ");
                }

                for (int i = 0; i < nPoints; i++)
                {
                    if (0 != i)
                    {
                        strcat(DecompBuffer, " ");
                    }

                    char buf[12];
                    sprintf(buf, "%04X", pts[i]);
                    strcat(DecompBuffer, buf);
                }
            }
            fprintf(fp, ";%s", DecompBuffer);

            int n;
            if (cp[pt].GetDecimalDigitValue(&n))
            {
                fprintf(fp, ";%d", n);
            }
            else
            {
                fprintf(fp, ";");
            }

            if (cp[pt].GetDigitValue(&n))
            {
                fprintf(fp, ";%d", n);
            }
            else
            {
                fprintf(fp, ";");
            }

            char *pNumericValue = NULL;
            if (cp[pt].GetNumericValue(&pNumericValue))
            {
                fprintf(fp, ";%s", pNumericValue);
            }
            else
            {
                fprintf(fp, ";");
            }

            if (cp[pt].GetBidiMirrored())
            {
                fprintf(fp, ";Y");
            }
            else
            {
                fprintf(fp, ";N");
            }

            char *pUnicode1Name = cp[pt].GetUnicode1Name();
            if (pUnicode1Name)
            {
                fprintf(fp, ";%s", pUnicode1Name);
            }
            else
            {
                fprintf(fp, ";");
            }

            char *pISOComment = cp[pt].GetISOComment();
            if (pISOComment)
            {
                fprintf(fp, ";%s", pISOComment);
            }
            else
            {
                fprintf(fp, ";");
            }

            UTF32 ptUpper = cp[pt].GetSimpleUppercaseMapping();
            if (UNI_EOF != ptUpper)
            {
                fprintf(fp, ";%04X", ptUpper);
            }
            else
            {
                fprintf(fp, ";");
            }

            UTF32 ptLower = cp[pt].GetSimpleLowercaseMapping();
            if (UNI_EOF != ptLower)
            {
                fprintf(fp, ";%04X", ptLower);
            }
            else
            {
                fprintf(fp, ";");
            }

            UTF32 ptTitle = cp[pt].GetSimpleTitlecaseMapping();
            if (UNI_EOF != ptTitle)
            {
                fprintf(fp, ";%04X", ptTitle);
            }
            else
            {
                fprintf(fp, ";");
            }

            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

void UniData::Prohibit(void)
{
    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (cp[pt].IsDefined())
        {
            bool bShouldProhibit = false;
            if (  0 != cp[pt].GetCombiningClass()
               || (cp[pt].GetCategory() & CATEGORY_OTHER))
            {
                bShouldProhibit = true;
            }

            if (cp[pt].GetCategory() == (CATEGORY_OTHER|SUBCATEGORY_PRIVATE_USE))
            {
                if (  (  0xE000 <= pt 
                      && pt <= 0xE0FF)
                   || ( 0xF8D0 <= pt
                      && pt <= 0xF8FF))
                {
                    // Tengwar and Klingon
                    //
                    bShouldProhibit = false;
                }
            }

            if (bShouldProhibit)
            {
                cp[pt].SetProhibited();
            }
        }
    }
}

void UniData::SaveClassifyPrintable(void)
{
    FILE *fp = fopen("cl_Printable.txt", "w+");
    if (NULL == fp)
    {
        return;
    }

    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (  cp[pt].IsDefined()
           && !cp[pt].IsProhibited())
        {
            fprintf(fp, "%04X;%s;%s;%d;%s", pt, cp[pt].GetDescription(), cp[pt].GetCategoryName(),
                cp[pt].GetCombiningClass(), cp[pt].GetBiDiName());

            char DecompBuffer[1024];
            DecompBuffer[0] = '\0';

            if (cp[pt].GetDecompositionType() != DECOMP_TYPE_NONE)
            {
                strcat(DecompBuffer, "<");
                strcat(DecompBuffer, cp[pt].GetDecompositionTypeName());
                strcat(DecompBuffer, ">");
            }

            UTF32 pts[30];
            int nPoints = cp[pt].GetDecompositionMapping(pts);

            if (nPoints != 1 || pts[0] != pt)
            {
                if ('\0' != DecompBuffer[0])
                {
                    strcat(DecompBuffer, " ");
                }

                for (int i = 0; i < nPoints; i++)
                {
                    if (0 != i)
                    {
                        strcat(DecompBuffer, " ");
                    }

                    char buf[12];
                    sprintf(buf, "%04X", pts[i]);
                    strcat(DecompBuffer, buf);
                }
            }
            fprintf(fp, ";%s", DecompBuffer);

            int n;
            if (cp[pt].GetDecimalDigitValue(&n))
            {
                fprintf(fp, ";%d", n);
            }
            else
            {
                fprintf(fp, ";");
            }

            if (cp[pt].GetDigitValue(&n))
            {
                fprintf(fp, ";%d", n);
            }
            else
            {
                fprintf(fp, ";");
            }

            char *pNumericValue = NULL;
            if (cp[pt].GetNumericValue(&pNumericValue))
            {
                fprintf(fp, ";%s", pNumericValue);
            }
            else
            {
                fprintf(fp, ";");
            }

            if (cp[pt].GetBidiMirrored())
            {
                fprintf(fp, ";Y");
            }
            else
            {
                fprintf(fp, ";N");
            }

            char *pUnicode1Name = cp[pt].GetUnicode1Name();
            if (pUnicode1Name)
            {
                fprintf(fp, ";%s", pUnicode1Name);
            }
            else
            {
                fprintf(fp, ";");
            }

            char *pISOComment = cp[pt].GetISOComment();
            if (pISOComment)
            {
                fprintf(fp, ";%s", pISOComment);
            }
            else
            {
                fprintf(fp, ";");
            }

            UTF32 ptUpper = cp[pt].GetSimpleUppercaseMapping();
            if (UNI_EOF != ptUpper)
            {
                fprintf(fp, ";%04X", ptUpper);
            }
            else
            {
                fprintf(fp, ";");
            }

            UTF32 ptLower = cp[pt].GetSimpleLowercaseMapping();
            if (UNI_EOF != ptLower)
            {
                fprintf(fp, ";%04X", ptLower);
            }
            else
            {
                fprintf(fp, ";");
            }

            UTF32 ptTitle = cp[pt].GetSimpleTitlecaseMapping();
            if (UNI_EOF != ptTitle)
            {
                fprintf(fp, ";%04X", ptTitle);
            }
            else
            {
                fprintf(fp, ";");
            }

            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

void UniData::SaveClassifyPrivateUse()
{
    FILE *fp = fopen("cl_PrivateUse.txt", "w+");
    if (NULL == fp)
    {
        return;
    }

    for (UTF32 pt = 0; pt <= codepoints; pt++)
    {
        if (  cp[pt].IsDefined()
           && (CATEGORY_OTHER|SUBCATEGORY_PRIVATE_USE) == cp[pt].GetCategory())
        {
            fprintf(fp, "%04X;%s\n", pt, cp[pt].GetDescription());
        }
    }
    fclose(fp);
}

char *CodePoint::GetCategoryName(void)
{
    int i = 0;
    while (CategoryTable[i].catlet)
    {
        if (CategoryTable[i].cat == m_category)
        {
            return CategoryTable[i].catlet;
        }
        i++;
    }
    return NULL;
}

char *CodePoint::GetBiDiName(void)
{
    int i = 0;
    while (BiDiTable[i].BiDiLet)
    {
        if (BiDiTable[i].BiDi == m_bidi)
        {
            return BiDiTable[i].BiDiLet;
        }
        i++;
    }
    return NULL;
}

char *CodePoint::GetDecompositionTypeName(void)
{
    int i = 0;
    while (DecompTypeTable[i].DecompTypeLet)
    {
        if (DecompTypeTable[i].DecompType == m_DecompType)
        {
            return DecompTypeTable[i].DecompTypeLet;
        }
        i++;
    }
    return NULL;
}

void UniData::LoadUnicodeHanFile(void)
{
    FILE *fp = fopen("UnicodeHan.txt", "r");
    if (NULL != fp)
    {
        char buffer[1024];
        while (NULL != ReadLine(fp, buffer, sizeof(buffer)))
        {
            int   nFields;
            char *aFields[2];

            ParseFields(buffer, 2, nFields, aFields);
            if (2 == nFields)
            {
                UTF32 pt1, pt2;
                char *p = strchr(aFields[0], '-');
                if (NULL != p)
                {
                    *p++ = '\0';
                    pt1 = DecodeCodePoint(aFields[0]);
                    pt2 = DecodeCodePoint(p);
                }
                else
                {
                    pt2 = DecodeCodePoint(aFields[0]);
                    pt1 = pt2;
                }

                for (UTF32 pt = pt1; pt <= pt2; pt++)
                {
                    if (cp[pt].IsDefined())
                    {
                        continue;
                    }

                    char hex[32];
                    char desc[1024];

                    sprintf(hex, "%04X", pt);
                    sprintf(desc, "%s CHARACTER %04X", aFields[1], pt);

                    int nFields1 = 15;
                    char *aFields1[15];
                    aFields1[0] = hex;
                    aFields1[1] = desc;
                    aFields1[2] = "So";
                    aFields1[3] = "0";
                    aFields1[4] = "ON";
                    aFields1[5] = "";
                    aFields1[6] = "";
                    aFields1[7] = "";
                    aFields1[8] = "";
                    aFields1[9] = "N";
                    aFields1[10] = "";
                    aFields1[11] = "";
                    aFields1[12] = "";
                    aFields1[13] = "";
                    aFields1[14] = "";

                    LoadUnicodeDataLine(pt, nFields1, aFields1);
                }
            }
        }
        fclose(fp);
    }
}
