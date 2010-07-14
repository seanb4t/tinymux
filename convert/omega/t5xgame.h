#ifndef _T5XGAME_H_
#define _T5XGAME_H_

#define T5X_V_MASK      0x000000FFUL
#define T5X_V_ZONE      0x00000100UL
#define T5X_V_LINK      0x00000200UL
#define T5X_V_DATABASE  0x00000400UL
#define T5X_V_ATRNAME   0x00000800UL
#define T5X_V_ATRKEY    0x00001000UL
#define T5X_V_PARENT    0x00002000UL
#define T5X_V_ATRMONEY  0x00008000UL
#define T5X_V_XFLAGS    0x00010000UL
#define T5X_V_POWERS    0x00020000UL
#define T5X_V_3FLAGS    0x00040000UL
#define T5X_V_QUOTED    0x00080000UL

#define T5X_MANDFLAGS_V2  (T5X_V_LINK|T5X_V_PARENT|T5X_V_XFLAGS|T5X_V_ZONE|T5X_V_POWERS|T5X_V_3FLAGS|T5X_V_QUOTED)
#define T5X_OFLAGS_V2     (T5X_V_DATABASE|T5X_V_ATRKEY|T5X_V_ATRNAME|T5X_V_ATRMONEY)

#define T5X_MANDFLAGS_V3  (T5X_V_LINK|T5X_V_PARENT|T5X_V_XFLAGS|T5X_V_ZONE|T5X_V_POWERS|T5X_V_3FLAGS|T5X_V_QUOTED|T5X_V_ATRKEY)
#define T5X_OFLAGS_V3     (T5X_V_DATABASE|T5X_V_ATRNAME|T5X_V_ATRMONEY)

#define A_USER_START    256     // Start of user-named attributes.

// Object types
//
#define T5X_TYPE_ROOM     0x0
#define T5X_TYPE_THING    0x1
#define T5X_TYPE_EXIT     0x2
#define T5X_TYPE_PLAYER   0x3
#define T5X_TYPE_GARBAGE  0x5
#define T5X_NOTYPE        0x7
#define T5X_TYPE_MASK     0x7

#define ATR_INFO_CHAR 0x01
#define T5X_NOTHING   (-1)

// Attribute flags
//
#define T5X_AF_ODARK    0x00000001UL
#define T5X_AF_DARK     0x00000002UL
#define T5X_AF_WIZARD   0x00000004UL
#define T5X_AF_MDARK    0x00000008UL
#define T5X_AF_INTERNAL 0x00000010UL
#define T5X_AF_NOCMD    0x00000020UL
#define T5X_AF_LOCK     0x00000040UL
#define T5X_AF_DELETED  0x00000080UL
#define T5X_AF_NOPROG   0x00000100UL
#define T5X_AF_GOD      0x00000200UL
#define T5X_AF_IS_LOCK  0x00000400UL
#define T5X_AF_VISUAL   0x00000800UL
#define T5X_AF_PRIVATE  0x00001000UL
#define T5X_AF_HTML     0x00002000UL
#define T5X_AF_NOPARSE  0x00004000UL
#define T5X_AF_REGEXP   0x00008000UL
#define T5X_AF_NOCLONE  0x00010000UL
#define T5X_AF_CONST    0x00020000UL
#define T5X_AF_CASE     0x00040000UL
#define T5X_AF_TRACE    0x00080000UL
#define T5X_AF_NONAME   0x00400000UL
#define T5X_AF_ISUSED   0x10000000UL

// Attribute numbers
//
#define T5X_A_PASS            5
#define T5X_A_QUOTA          49
#define T5X_A_LGET          127
#define T5X_A_MFAIL         128
#define T5X_A_LASTIP        144
#define T5X_A_COMJOIN       149
#define T5X_A_COMLEAVE      150
#define T5X_A_COMON         151
#define T5X_A_COMOFF        152
#define T5X_A_CMDCHECK      198
#define T5X_A_MONIKER       199
#define T5X_A_SPEECHMOD     215
#define T5X_A_CREATED       218
#define T5X_A_MODIFIED      219
#define T5X_A_CONNINFO      224
#define T5X_A_LMAIL         225
#define T5X_A_LOPEN         226
#define T5X_A_LASTWHISPER   227
#define T5X_A_ADESTROY      228
#define T5X_A_APARENT       229
#define T5X_A_ACREATE       230
#define T5X_A_LVISIBLE      231
#define T5X_A_IDLETMOUT     240
#define T5X_A_EXITFORMAT    241
#define T5X_A_CONFORMAT     242
#define T5X_A_NAMEFORMAT    243
#define T5X_A_DESCFORMAT    244

// Object Flagword 1
//
#define T5X_SEETHRU      0x00000008UL
#define T5X_WIZARD       0x00000010UL
#define T5X_LINK_OK      0x00000020UL
#define T5X_DARK         0x00000040UL
#define T5X_JUMP_OK      0x00000080UL
#define T5X_STICKY       0x00000100UL
#define T5X_DESTROY_OK   0x00000200UL
#define T5X_HAVEN        0x00000400UL
#define T5X_QUIET        0x00000800UL
#define T5X_HALT         0x00001000UL
#define T5X_TRACE        0x00002000UL
#define T5X_GOING        0x00004000UL
#define T5X_MONITOR      0x00008000UL
#define T5X_MYOPIC       0x00010000UL
#define T5X_PUPPET       0x00020000UL
#define T5X_CHOWN_OK     0x00040000UL
#define T5X_ENTER_OK     0x00080000UL
#define T5X_VISUAL       0x00100000UL
#define T5X_IMMORTAL     0x00200000UL
#define T5X_HAS_STARTUP  0x00400000UL
#define T5X_MUX_OPAQUE   0x00800000UL
#define T5X_VERBOSE      0x01000000UL
#define T5X_INHERIT      0x02000000UL
#define T5X_NOSPOOF      0x04000000UL
#define T5X_ROBOT        0x08000000UL
#define T5X_SAFE         0x10000000UL
#define T5X_ROYALTY      0x20000000UL
#define T5X_HEARTHRU     0x40000000UL
#define T5X_TERSE        0x80000000UL

// Object Flagword 2
//
#define T5X_KEY          0x00000001UL
#define T5X_ABODE        0x00000002UL
#define T5X_FLOATING     0x00000004UL
#define T5X_UNFINDABLE   0x00000008UL
#define T5X_PARENT_OK    0x00000010UL
#define T5X_LIGHT        0x00000020UL
#define T5X_HAS_LISTEN   0x00000040UL
#define T5X_HAS_FWDLIST  0x00000080UL
#define T5X_AUDITORIUM   0x00000100UL
#define T5X_ANSI         0x00000200UL
#define T5X_HEAD_FLAG    0x00000400UL
#define T5X_FIXED        0x00000800UL
#define T5X_UNINSPECTED  0x00001000UL
#define T5X_NO_COMMAND   0x00002000UL
#define T5X_CKEEPALIVE   0x00004000UL
#define T5X_NOBLEED      0x00008000UL
#define T5X_STAFF        0x00010000UL
#define T5X_HAS_DAILY    0x00020000UL
#define T5X_GAGGED       0x00040000UL
#define T5X_OPEN_OK      0x00080000UL
#define T5X_VACATION     0x01000000UL
#define T5X_PLAYER_MAILS 0x02000000UL
#define T5X_HTML         0x04000000UL
#define T5X_BLIND        0x08000000UL
#define T5X_SUSPECT      0x10000000UL
#define T5X_ASCII        0x20000000UL
#define T5X_CONNECTED    0x40000000UL
#define T5X_SLAVE        0x80000000UL

// Object Flagword 3
//
#define T5X_SITEMON      0x00000400UL
#define T5X_CMDCHECK     0x00000800UL
#define T5X_MUX_UNICODE  0x00001000UL
#define T5X_MARK_0       0x00400000UL
#define T5X_MARK_1       0x00800000UL
#define T5X_MARK_2       0x01000000UL
#define T5X_MARK_3       0x02000000UL
#define T5X_MARK_4       0x04000000UL
#define T5X_MARK_5       0x08000000UL
#define T5X_MARK_6       0x10000000UL
#define T5X_MARK_7       0x20000000UL
#define T5X_MARK_8       0x40000000UL
#define T5X_MARK_9       0x80000000UL

// Object Powerword 1
//
#define T5X_POW_CHG_QUOTAS  0x00000001UL
#define T5X_POW_CHOWN_ANY   0x00000002UL
#define T5X_POW_ANNOUNCE    0x00000004UL
#define T5X_POW_BOOT        0x00000008UL
#define T5X_POW_HALT        0x00000010UL
#define T5X_POW_CONTROL_ALL 0x00000020UL
#define T5X_POW_WIZARD_WHO  0x00000040UL
#define T5X_POW_EXAM_ALL    0x00000080UL
#define T5X_POW_FIND_UNFIND 0x00000100UL
#define T5X_POW_FREE_MONEY  0x00000200UL
#define T5X_POW_FREE_QUOTA  0x00000400UL
#define T5X_POW_HIDE        0x00000800UL
#define T5X_POW_IDLE        0x00001000UL
#define T5X_POW_SEARCH      0x00002000UL
#define T5X_POW_LONGFINGERS 0x00004000UL
#define T5X_POW_PROG        0x00008000UL
#define T5X_POW_SITEADMIN   0x00010000UL
#define T5X_POW_COMM_ALL    0x00080000UL
#define T5X_POW_SEE_QUEUE   0x00100000UL
#define T5X_POW_SEE_HIDDEN  0x00200000UL
#define T5X_POW_MONITOR     0x00400000UL
#define T5X_POW_POLL        0x00800000UL
#define T5X_POW_NO_DESTROY  0x01000000UL
#define T5X_POW_GUEST       0x02000000UL
#define T5X_POW_PASS_LOCKS  0x04000000UL
#define T5X_POW_STAT_ANY    0x08000000UL
#define T5X_POW_STEAL       0x10000000UL
#define T5X_POW_TEL_ANYWHR  0x20000000UL
#define T5X_POW_TEL_UNRST   0x40000000UL
#define T5X_POW_UNKILLABLE  0x80000000UL

// Object Powerword 2
//
#define T5X_POW_BUILDER     0x00000001UL

typedef unsigned char UTF8;

class P6H_LOCKEXP;
class T6H_LOCKEXP;

class T5X_LOCKEXP
{
public:
    typedef enum
    {
        le_is,
        le_carry,
        le_indirect,
        le_owner,
        le_and,
        le_or,
        le_not,
        le_attr,
        le_eval,
        le_ref,
        le_text,
        le_none,
    } T5X_OP;

    T5X_OP m_op;

    T5X_LOCKEXP *m_le[2];
    int          m_dbRef;
    char        *m_p[2];

    void SetIs(T5X_LOCKEXP *p)
    {
        m_op = le_is;
        m_le[0] = p;
    }
    void SetCarry(T5X_LOCKEXP *p)
    {
        m_op = le_carry;
        m_le[0] = p;
    }
    void SetIndir(T5X_LOCKEXP *p)
    {
        m_op = le_indirect;
        m_le[0] = p;
    }
    void SetOwner(T5X_LOCKEXP *p)
    {
        m_op = le_owner;
        m_le[0] = p;
    }
    void SetAnd(T5X_LOCKEXP *p, T5X_LOCKEXP *q)
    {
        m_op = le_and;
        m_le[0] = p;
        m_le[1] = q;
    }
    void SetOr(T5X_LOCKEXP *p, T5X_LOCKEXP *q)
    {
        m_op = le_or;
        m_le[0] = p;
        m_le[1] = q;
    }
    void SetNot(T5X_LOCKEXP *p)
    {
        m_op = le_not;
        m_le[0] = p;
    }
    void SetAttr(T5X_LOCKEXP *p, T5X_LOCKEXP *q)
    {
        m_op = le_attr;
        m_le[0] = p;
        m_le[1] = q;
    }
    void SetEval(T5X_LOCKEXP *p, T5X_LOCKEXP *q)
    {
        m_op = le_eval;
        m_le[0] = p;
        m_le[1] = q;
    }
    void SetRef(int dbRef)
    {
        m_op = le_ref;
        m_dbRef = dbRef;
    }
    void SetText(char *p)
    {
        m_op = le_text;
        m_p[0] = p;
    }

    void Write(FILE *fp);
    char *Write(char *p);

    bool ConvertFromP6H(P6H_LOCKEXP *p);
    bool ConvertFromT6H(T6H_LOCKEXP *p);

    T5X_LOCKEXP()
    {
        m_op = le_none;
        m_le[0] = m_le[1] = NULL;
        m_p[0] = m_p[1] = NULL;
        m_dbRef = 0;
    }
    ~T5X_LOCKEXP()
    {
        delete m_le[0];
        delete m_le[1];
        free(m_p[0]);
        free(m_p[1]);
        m_le[0] = m_le[1] = NULL;
        m_p[0] = m_p[1] = NULL;
    }
};

class T5X_ATTRNAMEINFO
{
public:
    bool  m_fNumAndName;
    int   m_iNum;
    char *m_pName;
    void  SetNumAndName(int iNum, char *pName);

    void Validate(int ver) const;

    void Write(FILE *fp, bool fExtraEscapes);

    void Upgrade();
    void Downgrade();

    T5X_ATTRNAMEINFO()
    {
        m_fNumAndName = false;
        m_pName = NULL;
    }
    ~T5X_ATTRNAMEINFO()
    {
        free(m_pName);
        m_pName = NULL;
    }
};

class T5X_ATTRINFO
{
public:
    char *m_pAllocated;

    bool m_fNumAndValue;
    int  m_iNum;
    char *m_pValueEncoded;
    void SetNumAndValue(int iNum, char *pValue);

    int  m_iFlags;
    int  m_dbOwner;
    char *m_pValueUnencoded;
    void SetNumOwnerFlagsAndValue(int iNum, int dbOwner, int iFlags, char *pValue);

    bool m_fIsLock;
    T5X_LOCKEXP *m_pKeyTree;

    enum
    {
        kNone,
        kEncode,
        kDecode,
    } m_kState;
    void EncodeDecode(int dbObj);

    void Validate() const;

    void Write(FILE *fp, bool fExtraEscapes) const;

    void Upgrade();
    void Downgrade();

    T5X_ATTRINFO()
    {
        m_fNumAndValue = false;
        m_pAllocated = NULL;
        m_pValueEncoded = NULL;
        m_pValueUnencoded = NULL;
        m_fIsLock = false;
        m_pKeyTree = NULL;
        m_iFlags = 0;
        m_dbOwner = T5X_NOTHING;
        m_kState = kNone;
    }
    ~T5X_ATTRINFO()
    {
        free(m_pAllocated);
        delete m_pKeyTree;
        m_pAllocated = NULL;
        m_pValueEncoded = NULL;
        m_pValueUnencoded = NULL;
        m_pKeyTree = NULL;
        m_iFlags = 0;
        m_dbOwner = T5X_NOTHING;
    }
};

class T5X_OBJECTINFO
{
public:
    bool m_fRef;
    int  m_dbRef;
    void SetRef(int dbRef) { m_fRef = true; m_dbRef = dbRef; }

    char *m_pName;
    void SetName(char *p);

    bool m_fLocation;
    int  m_dbLocation;
    void SetLocation(int dbLocation) { m_fLocation = true; m_dbLocation = dbLocation; }

    bool m_fContents;
    int  m_dbContents;
    void SetContents(int dbContents) { m_fContents = true; m_dbContents = dbContents; }

    bool m_fExits;
    int  m_dbExits;
    void SetExits(int dbExits) { m_fExits = true; m_dbExits = dbExits; }

    bool m_fNext;
    int  m_dbNext;
    void SetNext(int dbNext) { m_fNext = true; m_dbNext = dbNext; }

    bool m_fParent;
    int  m_dbParent;
    void SetParent(int dbParent) { m_fParent = true; m_dbParent = dbParent; }

    bool m_fOwner;
    int  m_dbOwner;
    void SetOwner(int dbOwner) { m_fOwner = true; m_dbOwner = dbOwner; }

    bool m_fZone;
    int  m_dbZone;
    void SetZone(int dbZone) { m_fZone = true; m_dbZone = dbZone; }

    bool m_fPennies;
    int  m_iPennies;
    void SetPennies(int iPennies) { m_fPennies = true; m_iPennies = iPennies; }

    bool m_fFlags1;
    int  m_iFlags1;
    void SetFlags1(int iFlags1) { m_fFlags1 = true; m_iFlags1 = iFlags1; }

    bool m_fFlags2;
    int  m_iFlags2;
    void SetFlags2(int iFlags2) { m_fFlags2 = true; m_iFlags2 = iFlags2; }

    bool m_fFlags3;
    int  m_iFlags3;
    void SetFlags3(int iFlags3) { m_fFlags3 = true; m_iFlags3 = iFlags3; }

    bool m_fPowers1;
    int  m_iPowers1;
    void SetPowers1(int iPowers1) { m_fPowers1 = true; m_iPowers1 = iPowers1; }

    bool m_fPowers2;
    int  m_iPowers2;
    void SetPowers2(int iPowers2) { m_fPowers2 = true; m_iPowers2 = iPowers2; }

    bool m_fLink;
    int  m_dbLink;
    void SetLink(int dbLink) { m_fLink = true; m_dbLink = dbLink; }

    bool m_fAttrCount;
    int  m_nAttrCount;
    vector<T5X_ATTRINFO *> *m_pvai;
    void SetAttrs(int nAttrCount, vector<T5X_ATTRINFO *> *pvai);

    T5X_LOCKEXP *m_ple;
    void SetDefaultLock(T5X_LOCKEXP *p) { free(m_ple); m_ple = p; }

    void Validate() const;

    void Write(FILE *fp, bool bWriteLock, bool fExtraEscapes);

    void Upgrade();
    void Downgrade();

    T5X_OBJECTINFO()
    {
        m_fRef = false;
        m_pName = NULL;
        m_fLocation = false;
        m_fContents = false;
        m_fExits = false;
        m_fNext = false;
        m_fParent = false;
        m_fOwner = false;
        m_fZone = false;
        m_fPennies = false;
        m_fPennies = false;
        m_fAttrCount = false;
        m_pvai = NULL;
        m_ple = NULL;
    }
    ~T5X_OBJECTINFO()
    {
        free(m_pName);
        delete m_ple;
        m_pName = NULL;
        m_ple = NULL;
        if (NULL != m_pvai)
        {
            for (vector<T5X_ATTRINFO *>::iterator it = m_pvai->begin(); it != m_pvai->end(); ++it)
            {
               delete *it;
            }
            delete m_pvai;
            m_pvai = NULL;
        }
    }
};


class T5X_GAME
{
public:
    int  m_flags;
    void SetFlags(int flags) { m_flags = flags; }
    int  GetFlags()          { return m_flags;  }

    bool m_fSizeHint;
    int  m_nSizeHint;
    void SetSizeHint(int nSizeHint) { m_fSizeHint = true; m_nSizeHint = nSizeHint; }

    bool m_fNextAttr;
    int  m_nNextAttr;
    void SetNextAttr(int nNextAttr) { m_fNextAttr = true; m_nNextAttr = nNextAttr; }

    bool m_fRecordPlayers;
    int  m_nRecordPlayers;
    void SetRecordPlayers(int nRecordPlayers) { m_fRecordPlayers = true; m_nRecordPlayers = nRecordPlayers; }

    vector<T5X_ATTRNAMEINFO *> m_vAttrNames;
    void AddNumAndName(int iNum, char *pName);

    map<int, T5X_OBJECTINFO *, lti> m_mObjects;
    void AddObject(T5X_OBJECTINFO *poi);

    void Pass2();

    void Validate() const;
    void ValidateFlags() const;
    void ValidateAttrNames(int ver) const;
    void ValidateObjects() const;

    void Write(FILE *fp);

    bool Upgrade3();
    bool Upgrade2();
    bool Downgrade1();
    bool Downgrade2();

    void ConvertFromP6H();
    void ConvertFromT6H();

    void ResetPassword();

    T5X_GAME()
    {
        m_flags = 0;
        m_fSizeHint = false;
        m_fNextAttr = false;
        m_fRecordPlayers = false;
    }
    ~T5X_GAME()
    {
        for (vector<T5X_ATTRNAMEINFO *>::iterator it = m_vAttrNames.begin(); it != m_vAttrNames.end(); ++it)
        {
            delete *it;
        }
        m_vAttrNames.clear();
        for (map<int, T5X_OBJECTINFO *, lti>::iterator it = m_mObjects.begin(); it != m_mObjects.end(); ++it)
        {
            delete it->second;
        }
        m_mObjects.clear();
    }
};

extern T5X_GAME g_t5xgame;
extern int t5xparse();
extern FILE *t5xin;

char *t5x_ConvertAttributeName(const char *);

#endif
