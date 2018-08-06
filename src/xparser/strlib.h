#ifndef STRLIB_H
#define STRLIB_H

extern bool char_isrus(char s);   // ������� ������
extern bool char_islat(char s);   // ��������� ������
extern bool char_ischar(char s);  // ������� ��� ��������� ������
extern bool char_isdigit(char s);  // �����
extern bool char_isspace(char s);
extern bool char_isupper(char s);
extern bool char_islower(char s);
extern char TOUPPER(char s);
extern char TOLOWER(char s);

// ������� ����� ��� ������ �� ��������
class STRING {
        char *String;
        int Length;
        void Allocated(int sz);
    public:
        // ������������
        STRING();       // ������� ������ ������
        STRING(int len);     // �������� ������ len ���� ������
        STRING(const char *str);   // ������� ������ ���������� ������
        STRING(const char *str, int len); // ������� ������ ���������� ������ ������ len
        STRING(const STRING &str);  // ����� �������
        virtual ~STRING();    // ����������

        bool IsEmpty(void);  // ���� ������ ���� ��� ������ �������, �� true
        void Empty(void);  // �������� ������

        int GetLength(void) const;   // �������� ����� ������
        char* GetString(void) const;  // �������� ���������
        char operator [](int index) const; // �������� ������
        char GetAt(int index) const;
        void SetAt(int index, char ch);

        void DeleteChar(int index);

        void Format(const char*, ...);  // ��������������� ������

        // �������� ������ �� ��������
        void operator =(const STRING &str);
        void operator +=(const STRING &str);
        void operator =(const char* str);
        void operator +=(const char* str);
        void operator +=(char s);
        STRING operator +(const STRING &str);
        // ������� ���������
        int Compare(const STRING& str) const;
        int Compare(const char* str) const;

        void MakeUpper(void); // ��� ������ � ������� �������
        void MakeLower(void); // ��� ������ � ������ �������
        void StrFormat(void); // ��� ������ � ������, � ������ ������ � �������
        void CAP(void);   // ������ ������ � ������� �������
        void DAP(void);   // ������ ������ � ������ �������
        bool StrFromFile(const char* fname); // ��������� �� �����
        void PruneCRLF(void); // ������� ������� 0A 0D � ����� ������

        STRING operator >>(STRING &str);

        int Atoi(void) const;
        int AHtoi(void) const;
        bool Atob(void) const;
        void KillSpaces(void); // ������� ������� � ������ � � ����� ������
};

bool operator ==(const STRING &str1, const STRING &str2);
bool operator ==(const STRING &str1, const char* str2);
bool operator ==(const char* str1, const STRING &str2);
bool operator !=(const STRING &str1, const STRING &str2);
bool operator !=(const STRING &str1, const char* str2);
bool operator !=(const char* str1, const STRING &str2);
bool operator <(const STRING &str1, const STRING &str2);
bool operator <(const STRING &str1, const char* str2);
bool operator <(const char* str1, const STRING &str2);
bool operator >(const STRING &str1, const STRING &str2);
bool operator >(const STRING &str1, const char* str2);
bool operator >(const char* str1, const STRING &str2);
bool operator <=(const STRING &str1, const STRING &str2);
bool operator <=(const STRING &str1, const char* str2);
bool operator <=(const char* str1, const STRING &str2);
bool operator >=(const STRING &str1, const STRING &str2);
bool operator >=(const STRING &str1, const char* str2);
bool operator >=(const char* str1, const STRING &str2);

extern const char* FormatStringForSave(const char* str);

#endif
