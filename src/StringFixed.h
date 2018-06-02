#ifndef _StringFixed_H
#define _StringFixed_H

#include "Arduino.h" 

#define STR_F(X) (String(F(X))) 

template <size_t N> 
class StringFixed {
public:
    StringFixed() { 
        str[N+1] = '\0';
        str[str_len = 0] = '\0'; 
    }    
    StringFixed(const char *s, const size_t count = 0){
        if (count == 0){
            strcpy(str, s);
        } else {
            strncpy(str, s, count);
        }        
        str[N+1] = '\0';
        str_len = strlen(str);        
    }        
    StringFixed(const String& s): StringFixed(s.c_str()) { }    
    StringFixed(const int i) {
        sprintf(str, "%d", i);
        str[N+1] = '\0';
        str_len = strlen(str);
    }
    StringFixed(const long i) {
        sprintf(str, "%ld", i);
        str[N+1] = '\0';
        str_len = strlen(str);
    }
    StringFixed(const float i) {
        sprintf(str, "%f", i);
        str[N+1] = '\0';
        str_len = strlen(str);
    }
    StringFixed(const double i) {
        sprintf(str, "%lf", i);
        str[N+1] = '\0';
        str_len = strlen(str);
    }
    StringFixed(StringFixed const&) = default;
    StringFixed(StringFixed&&) = default;
    ~StringFixed() = default;

    StringFixed& operator=(StringFixed const&) = default;
    StringFixed& operator=(StringFixed&&) = default; 

    char& operator[](size_t idx)       { return charAt(idx); }
    const char& operator[](size_t idx) const { return charAt(idx); }

    friend StringFixed& operator<<(StringFixed& l, const char r){
        l.concat(r);
        return l;
    }

    friend StringFixed& operator<<(StringFixed& l, const char* r){
        l.concat(r);
        return l;
    }

    template <size_t M> 
    friend StringFixed& operator<<(StringFixed& l, const StringFixed<M>& r){
        l.concat(r);
        return l;
    }

    friend StringFixed& operator+=(StringFixed& l, const char r){
        l.concat(r);
        return l;
    }

    friend StringFixed& operator+=(StringFixed& l, const char* r){
        l.concat(r);
        return l;
    }

    template <size_t M> 
    friend StringFixed& operator+=(StringFixed& l, const StringFixed<M>& r){
        l.concat(r);
        return l;
    }

    template <size_t M> 
    friend bool operator<(const StringFixed& l, const StringFixed<M>& r){ return (l.compareTo(r) < 0); }
    template <size_t M> 
    friend bool operator>(const StringFixed& l, const StringFixed<M>& r){ return (l.compareTo(r) > 0); }
    template <size_t M> 
    friend bool operator<=(const StringFixed& l, const StringFixed<M>& r){ return (l.compareTo(r) <= 0); }
    template <size_t M> 
    friend bool operator>=(const StringFixed& l, const StringFixed<M>& r){ return (l.compareTo(r) >= 0); }
    
    template <size_t M> 
    friend bool operator==(const StringFixed& l, const StringFixed<M>& r){ return l.equals(r); }
    template <size_t M> 
    friend bool operator!=(const StringFixed& l, const StringFixed<M>& r){ return !(l == r); }    

    char& charAt(const int i) { return str[i]; }
    const char& charAt(const int i) const{ return str[i]; }
    
    size_t length(){ return str_len; }

    char* c_str(){ return str; }
    
    template <size_t M> 
    int compareTo(const StringFixed<M>& str){ return this->compareTo(str.c_str()); }
    int compareTo(const char* str){ return strcmp(this->str, str); }

    template <size_t M> 
    bool equals(const StringFixed<M>& str2){ return (this->compareTo(str2) == 0); }
    
    bool concat(const char data){ 
        str[str_len++] = data;
        str[str_len] = '\0';
        return true; 
    }

    bool concat(const char* data){                
        int data_len = strlen(data);
        if (N - str_len - data_len < 0){
            return false;
        }
        for (int i = 0; i < data_len; i++) {
            str[str_len + i] = data[i];
        }
        str_len += data_len;
        str[str_len] = '\0';
        return true;
    }        

    template <size_t M> 
    bool concat(const StringFixed<M>& data){ return this->concat(data.c_str()); }                

    template <size_t M> 
    bool startsWith(const StringFixed<M>& str2){
        int i = 0;
        int j = 0;
        bool res = true;
        while (i < str_len && j < str2.length() && res) {
            res = res && (str[i++] == str2[j++]);            
        }        
        return res;
    }

    template <size_t M> 
    bool endsWith(const StringFixed<M>& str2){
        int i = str_len - 1;
        int j = str2.length() - 1;
        bool res = true;
        while (i >= 0 && j >= 0 && res) {
            res = res && (str[i--] == str2[j--]);            
        }        
        return res;
    }

    int indexOf(const char c, const size_t from = 0){        
        char *p = strchr(str+from, c);
        return (p != NULL ? p - str : -1);                
    }

    int indexOf(const char* s, const size_t from = 0){        
        char *p = strstr(str+from, s);        
        return (p != NULL ? p - str : -1);        
    }

    template <size_t M> 
    int indexOf(const StringFixed<M>& s, const size_t from = 0){    
        return this->indexOf(s.c_str(), from);
    }

    int lastIndexOf(const char c, const int from = 0){            
        int i;
        for (int i = str_len - from - 1; i >= 0; i--) {
            if (str[i] == c){
                return i;
            }
        }        
        return -1;
    }

    int lastIndexOf(const char* s, const size_t from = 0){            
        int i;
        const int k_len = strlen(s);
        int k = k_len - 1;         
        for (i = str_len - from - 1; (i >= 0 && k >= 0); i--) {
            if (str[i] == s[k]){
                k--;
            } else {
                k = k_len - 1;
            }
        }        
        return i;
    }

    template <size_t M> 
    int lastIndexOf(const StringFixed<M>& s, const size_t from = 0){            
        int i;        
        int k = s.length() - 1;         
        for (i = str_len - from - 1; (i >= 0 && k >= 0); i--) {
            if (str[i] == s.charAt(k)){
                k--;
            } else {
                k = s.length() - 1;
            }
        }        
        return i;
    }

    void remove(const size_t index, const size_t count = 1){
        int i;
        for (i = index; i + count < str_len; i++) {
            str[i] = str[i+count];
        }    
        str[i] = '\0';    
        str_len -= count;
    }

    template <size_t M> 
    void copy(StringFixed<M>& src, size_t index = 0, size_t end_index = 0){        
        char *begin = src.c_str() + index;
        char *end = src.c_str() + (end_index != 0 ? end_index : src.length());
        char c = *end;
        *end = '\0';        
        this->concat(begin);
        *end = c;
    }        

    template <size_t M> 
    void substring(StringFixed<M>& dest, size_t index = 0, size_t end_index = 0){
        char *begin = str + index;
        char *end = str + (end_index != 0 ? end_index : str_len);
        char c = *end;
        *end = '\0';        
        dest.concat(begin);
        *end = c;
    }
    
private:    
    char   str[N+1];    
    size_t str_len;
};

#endif  // _StringFixed_H 
