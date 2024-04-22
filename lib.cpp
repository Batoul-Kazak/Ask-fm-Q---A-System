// #include "lib.h"
// #include<iostream>
// #include<bits/stdc++.h>
// using namespace std;



// int convert_char_to_signed_integer(char ch)
// {
//     if (ch == (char) 48) return 0;
//     if (ch >= (char) 49 && ch <= (char) 57) return ((int) ch - 48);
//     return -1;
// }

// bool is_symbol(char ch)
// {
//     if ((ch >= (char) 33 && ch <= (char) 47) ||
//         (ch >= (char) 58 && ch <= (char) 63) ||
//         (ch >= (char) 91 && ch <= (char) 96) ||
//         (ch >= (char) 123 && ch <= (char) 126)) return true;

//     return false;
// }

// string extract_email_from_line(string file_line)
// {
//     int index = -1;
//     string email = "";
//     for (size_t i = 0; i < file_line.size(); i++)
//     {
//         if (file_line[i] == '@')
//             index = i;
//     }

//     if (index == -1) return "email doesn't exists in the line";

//     for (size_t i = index; i >= 0; i--)
//     {
//         if (file_line[i] == ' ') break;

//         email += file_line[i];
//     }

//     reverse(email.begin(), email.end());
//     email += "gmail.com";
//     return email;
// }

// string extract_password_from_sign_up_file(string file_line)
// {
//     string password_ = "";
//     int space = 0;
//     for (size_t i = 0; i < file_line.size(); i++)
//     {
//         if (file_line[i] == ' ') { space++; continue; }

//         if (space < 3) continue;

//         password_ += file_line[i];
//     }
//     return password_;
// }

// string extract_name_from_sign_up_file(string file_line)
// {

//     int space = 0;
//     string name = "";
//     bool start = false;
//     for (size_t i = 1; i < file_line.size(); i++)
//     {
//         if (space == 3) return name;

//         if (file_line[i] == ' ') space++;

//         if (space < 2) continue;

//         if (start && file_line[i] != ' ')
//             name += file_line[i];

//         if (space == 2) start = true;
//     }
//     return "error in signed up users file";
// }

// int convert_string_to_integer(string str) //234
// {
//     int result = 0;
//     int d = 1;
//     for (size_t i = str.size() - 1; i >= 0; i--)
//     {
//         if (convert_char_to_signed_integer(str[i]) == -1) { return result; }
//         result += d * convert_char_to_signed_integer(str[i]);
//         // cout << i << " result: " << result << "\n";
//         d *= 10;
//     }
//     return result;
// }

// string convert_int_to_string(int num) //1 2 3 4 5 6 7
// {
//     string result = "";
//     int d = 1;
//     int x = num;
//     while (num > 0)
//     {
//         x = num % 10;
//         result += to_string(x);

//         num /= 10;
//     }

//     reverse(result.begin(), result.end());

//     return result;
// }

// string replace_texts_in_the_line(string line, string old_text, string new_text)
// {
//     int old_start,
//         new_start,
//         new_end;
//     old_start = new_start = new_end = -1;

//     string s = "";
//     bool found = false; //7 rama@gmail.com Rama FJKhj2kdjfgnkjw35
//     int index = 0;
//     for (size_t i = 0; i < line.size(); i++)
//     {
//         if (s == old_text) break;

//         if (line[i] == old_text[index])
//         {
//             if (!found) old_start = i;
//             found = true;
//             index++;
//             s += line[i];
//         }

//         if (line[i] != old_text[i] && index < old_text.size() && found)
//         {
//             found = false;
//             index = 0;
//             s = "";
//         }
//     }

//     // cout << s << endl;
//     return s;
// }

