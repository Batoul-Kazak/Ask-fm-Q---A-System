#include "lib.h"

const int MAX_USERS = 20,
MAX_GENERAL_QUESTIONS = 20,
MAX_SUB_QUESTIONS = 20;

const string signed_up_users_path = "Files/signed_up_users.txt",
current_login_users_path = "Files/current_login_users.txt",
questions_path = "Files/questions.txt",
answers_path = "Files/answers.txt";

string convert_int_to_string(int num) //1 2 3 4 5 6 7
{
    string result = "";
    int d = 1;
    int x = num;
    while (num > 0)
    {
        x = num % 10;
        result += to_string(x);

        num /= 10;
    }

    reverse(result.begin(), result.end());

    return result;
}

int convert_char_to_signed_integer(char ch)
{
    if (ch == (char) 48) return 0;
    if (ch >= (char) 49 && ch <= (char) 57) return ((int) ch - 48);
    return -1;
}

bool is_symbol(char ch)
{
    if ((ch >= (char) 33 && ch <= (char) 47) ||
        (ch >= (char) 58 && ch <= (char) 63) ||
        (ch >= (char) 91 && ch <= (char) 96) ||
        (ch >= (char) 123 && ch <= (char) 126)) return true;

    return false;
}

int convert_string_to_integer(string str) //234
{
    int result = 0;
    int d = 1;
    for (size_t i = str.size() - 1; i >= 0; i--)
    {
        if (convert_char_to_signed_integer(str[i]) == -1) { return result; }
        result += d * convert_char_to_signed_integer(str[i]);
        // cout << i << " result: " << result << "\n";
        d *= 10;
    }
    return result;
}

int extract_id_from_line(string line)
{
    string id = "";
    for (size_t i = 0; i < line.size(); i++)
    {
        if (convert_char_to_signed_integer(line[i]) == -1) break;
        id += line[i];
    }
    if (id != "")
        return convert_string_to_integer(id);
    else return -1;
}

string extract_email_from_line(string file_line)
{
    int index = -1;
    string email = "";
    for (size_t i = 0; i < file_line.size(); i++)
    {
        if (file_line[i] == '@')
            index = i;
    }

    if (index == -1) return "email doesn't exists in the line";

    for (size_t i = index; i >= 0; i--)
    {
        if (file_line[i] == ' ') break;

        email += file_line[i];
    }

    reverse(email.begin(), email.end());
    email += "gmail.com";
    return email;
}

string extract_password_from_sign_up_file(string file_line)
{
    string password_ = "";
    int space = 0;
    for (size_t i = 0; i < file_line.size(); i++)
    {
        if (file_line[i] == ' ') { space++; continue; }

        if (space < 3) continue;

        password_ += file_line[i];
    }
    return password_;
}

string extract_name_from_line(string line)
{
    int space = 0;
    string name = "";
    bool start = false;
    for (size_t i = 1; i < line.size(); i++)
    {
        if (space == 3) return name;

        if (line[i] == ' ') space++;

        if (space < 2) continue;

        if (start && line[i] != ' ')
            name += line[i];

        if (space == 2) start = true;
    }
    return "error in signed up users file";
}

string replace_texts_in_the_line(string line, string old_text, string new_text)
{
    int old_start,
        new_start,
        new_end;
    old_start = new_start = new_end = -1;

    string s = "";
    bool found = false; //7 rama@gmail.com Rama FJKhj2kdjfgnkjw35
    int index = 0;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (s == old_text) break;

        if (line[i] == old_text[index])
        {
            if (!found) old_start = i;
            found = true;
            index++;
            s += line[i];
        }

        if (line[i] != old_text[i] && index < old_text.size() && found)
        {
            found = false;
            index = 0;
            s = "";
        }
    }

    // cout << s << endl;
    return s;
}

int return_file_lines_number(string file_path)
{
    int lines_number = 0;
    fstream file_handler(file_path.c_str());

    if (file_handler.fail())
    {
        cout << "Error opening the file\n";
        cout << "Problems might be:\n";
        cout << "\t 1. Error in path \n";
        cout << "\t 2. The file doesn't exists\n";
        cout << "\t 2. The file exists out current directory\n";
    }

    string line;
    while (getline(file_handler, line))
    {
        lines_number++;
    }
    return lines_number;
}

//these methods work on answers file and questions file because they have the same structure
int extract_question_id(string line)
{
    //33 5 hhh
    return extract_id_from_line(line); //the purpose from writing the function again is to work on more clear name 
    //that will make the operation more readable
}

int extract_user_id_from_question_or_answer_file(string line)
{
    int id = -1;
    string result = "";
    int found = 0;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ')
        {
            found++;
            continue;
        }

        if (!found) continue;
        if (found == 2) return convert_string_to_integer(result);

        result += line[i];
    }
    return -1;
}

