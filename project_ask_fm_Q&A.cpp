
// #include <limits>
#include<iostream>
#include<bits/stdc++.h>
#include<sstream>
#include<fstream>
#include "lib.h"
using namespace std;

struct user
{
    string name;
    string password;
    string email;
    string path = "signed_up_users.txt";
    int id;
    // int len;
    vector<int> login_users_vector;
    vector<int> signed_in_users_vector;

    // int return_the_last_line()
    // {
    //     fstream file_handler(signed_up_users_path.c_str());

    //     string line;
    //     int line_num = 0;
    //     while (getline(file_handler, line))
    //         line_num++;
    //     return line_num;
    // }

    user()
    {
        name = "";
        password = "";
        email = "@gmail.com";
        id = -1;
        // len = return_the_last_line();
    }

    bool check_if_user_signed_up_by_id(int id)
    {
        fstream file_handler(signed_up_users_path.c_str());

        if (file_handler.fail())
        {
            cout << "Can't open the login_users file!\n";
            return false;
        }

        string line;
        while (getline(file_handler, line))
        {
            if (extract_id_from_line(line) == id)
            {
                file_handler.close();
                return true;
            }
        }
        file_handler.close();
        return false;
    }

    int generate_id_for_new_user()
    {
        update_signed_in_users_ids_vector();

        int id;
        for (size_t i = 0; i < signed_in_users_vector.size(); i++)
        {
            if (check_if_user_signed_up_by_id(i + 1)) continue;
            id = i + 1;
            return id;
        }

        id = signed_in_users_vector.size() + 1;
        return id;
    }

    bool check_if_user_login_by_id(int id)
    {
        ifstream file_handler(current_login_users_path.c_str());

        if (file_handler.fail())
        {
            cout << "Failed to open current_login_users file\n";
            return false;
        }

        string line;
        int loop = 1;
        while (getline(file_handler, line))
        {
            if (extract_id_from_line(line) == id)
            {
                // cout << id << " " << return_user_id_from_line(line) << " " << loop << endl;
                file_handler.close();
                return true;
            }
            loop++;
        }
        if (extract_id_from_line(line) == -1) cout << "No users login at the moment\n";
        file_handler.close();
        return false;
    }

    string return_user_name_by_id(int id)
    {
        string name;
        fstream file_handler(signed_up_users_path);

        if (id == -2) return "Anonymous";

        if (file_handler.fail())
        {
            cout << "Failed to open sign up users file\n";
            return "Failed to open";
        }

        string line;
        while (getline(file_handler, line))
        {
            int user_id = extract_id_from_line(line);
            if (user_id == id)
                return extract_name_from_line(line);
        }
        return "Not Found User";
    }

    bool password_validation(string password)
    {
        if (password.size() < 8)  return false;
        int okay = 0;
        bool upper = false;
        bool number = false;
        for (size_t i = 0; i < password.size(); i++)
        {
            if (password[i] >= (char) 65 && password[i] <= (char) 90)
                okay++, upper = true;

            if (password[i] >= (char) 48 && password[i] <= (char) 57)
                okay++, number = true;

        }
        if (!upper) cout << "No upper case letter exists\n";
        if (!number) cout << "No number exists\n";
        if (okay < 8) cout << "Password should be at least 8 characters\n";

        if (okay < 2 || !upper || !number) return false;
        return true;
    }

    bool email_validation(string email)
    {
        int number = convert_char_to_signed_integer(email[0]);
        if (email[0] == '@' || number != -1)
        {
            cout << "Email mustn't start with a number\n";
            return false;
        }

        string suffix = "gmail.com";
        int found = false, index = 0, dot = 0;
        for (size_t i = 0; i < email.size(); i++)
        {
            if (email[i] == '.' && !found)
            {
                cout << "Email can't contain dot before @\n";
                return false;
            }

            if (is_symbol(email[i]) && email[i] != '@' && email[i] != '.') {
                cout << "Email mustn't contain a symbol\n";
                return false;
            }

            if (email[i] == '.') dot++;

            if (dot > 1)
            {
                cout << "Email can't contain more than one dot (.)\n";
                return false;
            }

            if (email[i] == '@') { found++; continue; }

            if (!found) continue;

            if (found > 1)
            {
                cout << "Email can't contain more than one '@'\n";
                return false;
            }

            if (email[i] != suffix[index]) {
                cout << "Email should be like name@gmail.com\n";
                return false;
            }
            index++;
        }
        if (!found) {
            cout << "Email should be like name@gmail.com\n";
            return false;
        }
        return true;
    }

    bool name_validation(string name)
    {
        if (name[0] < 'A' || name[0] > 'Z')
        {
            cout << "Name should begin with capital letter\n";
            cout << name[0] << " " << 'N' << endl;
            return false;
        }

        for (size_t i = 1; i < name.size(); i++)
        {
            if (is_symbol(name[i]) || convert_char_to_signed_integer(name[i]) != -1)
            {
                cout << "Name shouldn't contain a symbol or a number\n";
                return false;
            }

            if (name[i] >= 'A' && name[i] <= 'Z')
            {
                cout << "Name shouldn't contain a capital letter in the middle\n";
                return false;
            }
        }
        return true;
    }

    string return_signed_up_user_line_by_id(int id)
    {
        fstream file_handler(signed_up_users_path.c_str());

        if (file_handler.fail())
        {
            cout << "Can't open login_users file\n";
            return "Error";
        }

        string line;
        string id_ = "";
        while (getline(file_handler, line))
        {
            for (size_t i = 0; i < line.size(); i++)
            {
                if (line[i] == ' ') break;
                id_ += line[i];
            }

            if (convert_string_to_integer(id_) == id)
            {
                file_handler.close();
                return line;
            }
            id_ = " ";
        }
        file_handler.close();
        return "error";
    }

    int check_if_user_signed_up_by_email_and_return_his_id(string email)
    {
        fstream file_handler(path.c_str());

        if (file_handler.fail())
        {
            cout << "Couldn't open the user_signed_up file\n";
            return -1;
        }

        string line, l_;
        while (getline(file_handler, line))
        {
            string email_ = extract_email_from_line(line);
            if (email == "email doesn't exists in the line") continue;

            if (email_ == email)
            {
                l_ = line;
                break;
            }
        }
        int id_ = extract_id_from_line(l_);
        return id_;
    }

    bool sign_up()
    {
        if (signed_in_users_vector.size() == MAX_USERS)
        {
            cout << "Can't add more users!\n";
            return false;
        }

        cout << "Enter username, password, email:\n";
        cin >> name >> email >> password;

        name_validation(name);
        email_validation(email);
        password_validation(password);

        if (!name_validation(name) || !password_validation(password) || !email_validation(email))
            return sign_up();

        if (check_if_user_signed_up_by_email_and_return_his_id(email) != -1)
        {
            cout << "This email already signed up!\n";
            return sign_up();
        }

        bool visible_account = false;
        cout << "Do you want your answers and questions to be visible to other users?\n";
        cout << "Enter 1 for yes and 0 for no\n";
        cin >> visible_account;

        int id;
        if (visible_account)
        {
            id = generate_id_for_new_user();
            cout << "Your id is: " << id << endl;
        }
        else
        {
            id = 0;
            cout << "You don't have id, Some operations won't be available for you\n";
        }

        fstream file_handler(signed_up_users_path.c_str(), ios::app);
        if (file_handler.fail())
        {
            cout << "Failed to open signed up users file\n";
            return false;
        }

        // int lines_number = return_file_lines_number(signed_up_users_path);

        file_handler << id << " " << email << " " << name << " " << password << "\n";

        cout << "You signed up to the system successfully!\n";
        file_handler.close();
        return true;
    }

    // COMPLETE THE REPLACE FUNCTION IN THE PROJECT lib.h
    void reset_password(int id)
    {
        //     string new_password;
        //     cout << "Enter the new password:\n";
        //     cin >> new_password;

        //     if (!password_validation(password))
        //         return reset_password(id);

        //     fstream file_handler(signed_up_users_path.c_str());

        //     string line; //don't use the return_signed_up_user_line_by_id function
        //     string id_ = "";  //because i need to edit on the file 
        //     string password;
        //     while (getline(file_handler, line))
        //     {
        //         for (size_t i = 0; i < line.size(); i++)
        //         {
        //             if (line[i] == ' ') break;
        //             id_ += line[i];
        //         }

        //         // if (convert_string_to_integer(id_) == id)
        //         // {
        //         //     password = return_password_from_signed_up_file(line);
        //         //     // line.replace(line.find(password), line.length(), new_password);
        //         // }
        //     }

            // THE RIGHT WAY :
            // while (getline(file_handler, line)) { // Loop through each line in the input file
            //     size_t pos = line.find(searchWord); // Find the position of the search word in the line

            //     while (pos != std::string::npos) { // Repeat until all occurrences are replaced
            //         line.replace(pos, searchWord.length(), replaceWord); // Replace the search word with the replace word
            //         pos = line.find(searchWord, pos + replaceWord.length()); // Find the next occurrence of the search word
            //     }
            //     outputFile << line << "\n"; // Write the modified line to the output file
            // }
    }

    void login(int trials = 3)
    {
        if (trials == 0)
        {
            cout << "Your attempts were wrong, Try later\n";
            return;
        }
        if (trials < 3) cout << "Error in Password, Try again\n";

        string email, password;
        cout << "Enter your email and password\n";
        cin >> email >> password;

        int id = check_if_user_signed_up_by_email_and_return_his_id(email);
        if (id == -1)
        {
            cout << "You are not signed up\n";
            return;
        }

        string line = return_signed_up_user_line_by_id(id);

        string name = extract_name_from_line(line);

        string password_ = extract_password_from_sign_up_file(line);

        if (password_ != password)
        {
            cout << "Wrong password, Try again\n";
            return login(trials - 1);
        }

        fstream file_handler(signed_up_users_path.c_str());
        string line_;
        string user_line = "";
        while (getline(file_handler, line_))
        {
            if (extract_id_from_line(line_) == id)
            {
                user_line = line_;
                break;
            }
        }

        fstream file_handler_2(current_login_users_path.c_str(), ios::app);

        if (file_handler_2.fail())
        {
            cout << "Can't open current_login_users file\n";
            return;
        }

        file_handler_2 << user_line << "\n";
        file_handler_2.close();

        cout << name << " login successfully!\n";
    }

    int read_user_info_for_sign_login_out()
    {
        int id;
        string password;
        cout << "Enter your id:\n";
        cin >> id;

        cout << "Enter your email and password to confirm its you:\n";
        cin >> email >> password;

        string l_ = return_signed_up_user_line_by_id(id);

        if (l_ == "error" || l_.size() < 10)
        {
            cout << "Couldn't find the user\n";
            return -1;
        }

        string email_ = extract_email_from_line(l_);
        string password_ = extract_password_from_sign_up_file(l_);

        if (password != password_)
        {
            cout << "Error in password, Try again\n";
            return -1;
        }

        if (email != email_)
        {
            cout << "Email doesn't exists, Try again\n";
            return -1;
        }
        return id;
    }

    bool logout()
    {
        int id = read_user_info_for_sign_login_out();
        cout << "id: " << id << endl;

        if (id == -1) return false;

        if (!check_if_user_login_by_id(id))
        {
            cout << "This id is not logging\n";
            return false;
        }

        fstream reader;
        reader.open(current_login_users_path);

        if (reader.fail())
        {
            cout << "Failed to open current_login_users file!\n";
            return false;
        }

        vector <string>lines;

        string line;
        // bool found = false;
        while (getline(reader, line))
        {
            if (extract_id_from_line(line) != id)
                lines.push_back(line);
        }

        reader.close();

        ofstream writer;

        writer.open(current_login_users_path);

        if (writer.fail())
        {
            cout << "Failed to open current_login_users file!\n";
            return false;
        }

        for (size_t i = 0; i < lines.size(); i++)
            writer << lines[i] << "\n";

        return true;
    }

    //THIS METHOD IF USER WANTED TO UPDATE SIGNED UP USERS MANUALLY
    void update_signed_in_users_ids_vector()
    {
        fstream file_handler(signed_up_users_path.c_str());

        signed_in_users_vector.clear();

        string line;
        while (getline(file_handler, line))
            signed_in_users_vector.push_back(extract_id_from_line(line));

        file_handler.close();
    }

    //THIS FUNCTION IF USER WANTED TO UPDATE LOGIN USERS MANUALLY
    void update_login_users_ids_vector()
    {
        fstream file_handler(current_login_users_path.c_str());

        login_users_vector.clear();

        string line;
        while (getline(file_handler, line))
            login_users_vector.push_back(extract_id_from_line(line));

        file_handler.close();
    }

    //just to make sure that it is updating when a user signUp/logOut/signIn/Login 
    void print_vector()
    {
        for (size_t i = 0; i < signed_in_users_vector.size(); i++)
        {
            cout << signed_in_users_vector[i] << " ";
        }
        cout << "\n";

        for (size_t i = 0; i < login_users_vector.size(); i++)
        {
            cout << login_users_vector[i] << " ";
        }
    }

    bool sign_out()
    {
        int id = read_user_info_for_sign_login_out();

        if (id == -1) return false;

        if (!check_if_user_signed_up_by_id(id))
        {
            cout << "This id is not signed in\n";
            return false;
        }
        // 11 fatima@gmail.com fatima fatiMa446543

        char okay;
        cout << "Are you sure you want to sign out? (y/n)\n";
        cin >> okay;

        if (okay == 'n') return false;

        fstream reader;
        reader.open(signed_up_users_path);

        if (reader.fail())
        {
            cout << "Failed to open sign_in_users file!\n";
            return false;
        }

        vector <string>lines;

        string line;
        while (getline(reader, line))
        {
            if (extract_id_from_line(line) != id)
                lines.push_back(line);
        }

        reader.close();

        ofstream writer;

        writer.open(signed_up_users_path);

        if (writer.fail())
        {
            cout << "Failed to open sign_in_users file!\n";
            return false;
        }

        for (size_t i = 0; i < lines.size(); i++)
            writer << lines[i] << "\n";

        return true;
    }

    void list_system_users()
    {
        fstream file_handler(signed_up_users_path.c_str());

        if (file_handler.fail())
        {
            cout << "Failed to open sign up users file\n";
            return;
        }

        string line;
        while (getline(file_handler, line))
        {
            if (extract_id_from_line(line) == 0)
            {
                cout << "Anonymous User\n";
                cout << "_________________________________________\n";
            }
            else {
                cout << extract_name_from_line(line) << "\n";
                cout << "\thas id: " << extract_id_from_line(line) << "\n";
                cout << "\tand his/her email is: " << extract_email_from_line(line) << "\n";
                cout << "_________________________________________\n";
            }
        }
    }
};

struct question
{
    int question_id;
    int user_id;
    string question_content;
    int answers_num_available;

    user user_;

    //this will list all questions that asked with user id

    string extract_question_by_id(int id)
    {
        fstream file_handler(questions_path);

        if (file_handler.fail())
        {
            cout << "Sorry couldn't open questions file, We will fix this problem soon\n";
            return "Error";
        }

        string line;
        string required_line;
        while (getline(file_handler, line))
        {
            if (extract_question_id(line) == id)
            {
                required_line = line;
                break;
            }
        }

        int spaces = 0;
        string result = "";
        for (size_t i = 0; i < required_line.size(); i++)
        {
            if (line[i] == ' ' && spaces < 2) { spaces++; continue; }

            if (spaces < 2) continue;

            result += line[i];
        }

        if (result == "") { file_handler.close(); return "Error"; }
        file_handler.close();
        return result;
    }

    string extract_answer_by_id(int id)
    {
        fstream file_handler(answers_path);

        if (file_handler.fail())
        {
            cout << "Sorry couldn't open answers file, We will fix this problem soon\n";
            return "Error";
        }

        string line;
        string required_line;
        while (getline(file_handler, line))
        {
            if (extract_question_id(line) == id) //this method works also in answers file
            {
                required_line = line;
                break;
            }
        }

        int spaces = 0;
        string result = "";
        for (size_t i = 0; i < required_line.size(); i++)
        {
            if (line[i] == ' ' && spaces < 2) { spaces++; continue; }

            if (spaces < 2) continue;

            result += line[i];
        }

        if (result == "") { file_handler.close(); return "Error"; }
        file_handler.close();
        return result;
    }

    bool check_if_question_belongs_to_user(int question_id, int user_id)
    {
        fstream file_handler(questions_path);

        if (file_handler.fail())
        {
            cout << "Sorry couldn't open question file, We will fix this problem soon\n";
            return false;
        }

        string line;
        while (getline(file_handler, line))
        {
            if (extract_user_id_from_question_or_answer_file(line) == user_id)
                if (extract_question_id(line) == question_id)
                    return true;
        }
        return false;
    }

    void print_all_questions()
    {
        fstream question_file_handler(questions_path.c_str());

        if (question_file_handler.fail())
        {
            cout << "Sorry couldn't open questions file, We will fix this problem soon\n";
            return;
        }

        fstream answers_file_handler(answers_path.c_str());

        if (answers_file_handler.fail())
        {
            cout << "Sorry couldn't open answers file, We will fix this problem soon\n";
            return;
        }

        string question_line;
        string answer_line;
        while (getline(question_file_handler, question_line))
        {
            int question_id = extract_question_id(question_line);
            cout << "Question number " << question_id << " from user id " << extract_user_id_from_question_or_answer_file(question_line) << "          Question: " << extract_question_by_id(extract_question_id(question_line)) << "\n";
            while (getline(answers_file_handler, answer_line))
            {
                if (extract_question_id(answer_line) == question_id)
                {
                    cout << "Answer: " << extract_answer_by_id(question_id) << "\n";
                    cout << "\n";
                    break;
                }
            }
        }
        question_file_handler.close();
    }


    //this will list all questions from the user that is asking
    void print_questions_from_user(int user_id)
    {
        fstream question_file_handler(questions_path.c_str());

        if (question_file_handler.fail())
        {
            cout << "Sorry couldn't open questions file, We will fix this problem soon\n";
            return;
        }

        fstream answers_file_handler(answers_path.c_str());

        if (answers_file_handler.fail())
        {
            cout << "Sorry couldn't open answers file, We will fix this problem soon\n";
            return;
        }

        string question_line;
        string answer_line;
        while (getline(question_file_handler, question_line))
        {
            int question_id = extract_question_id(question_line);
            int user_id_who_asked = extract_user_id_from_question_or_answer_file(question_line);

            if (user_id_who_asked != user_id) continue;
            cout << "Question number " << question_id << " From You,  Question: " << extract_question_by_id(extract_question_id(question_line)) << "\n";
            while (getline(answers_file_handler, answer_line))
            {
                int user_id_who_answered = extract_user_id_from_question_or_answer_file(answer_line);
                string user_name_who_answered = user_.return_user_name_by_id(user_id_who_answered);

                if (user_name_who_answered == "Not Found User")
                    user_name_who_answered = "Deleted Account";

                if (extract_question_id(answer_line) == question_id)
                {
                    cout << "Answered from: " << user_name_who_answered << "   Answer: " << extract_answer_by_id(question_id) << "\n";
                    cout << "\n";
                    break;
                }
            }
        }
        question_file_handler.close();
    }

    int extract_answer_id_from_line(string line)
    {
        int spaces = 0;
        string id = "";
        for (size_t i = 0; i < line.size(); i++)
        {
            if (line[i] == ' ' && spaces == 2) break;
            if (line[i] == ' ') { spaces++; continue; }

            if (spaces == 2)
                id += line[i];
        }

        return convert_string_to_integer(id);
    }

    int return_new_id_for_new_answer(int question_id)
    {
        fstream file_handler(answers_path);

        if (file_handler.fail())
        {
            cout << "Failed to open answers file\n";
            return -1;
        }

        string line;
        int new_id;
        while (getline(file_handler, line))
        {
            //use extract_answer_id_from_line function
            if (extract_question_id(line) == question_id)
                new_id = extract_answer_id_from_line(line);
        }
        return new_id + 1;
    }

    bool answer_question(int question_id, int user_id)
    {
        string answer;
        cout << "Enter your answer: \n";
        getline(cin, answer);

        fstream file_handler(answers_path.c_str(), ios::app);

        if (file_handler.fail())
        {
            cout << "Failed to open answers_file\n";
            return false;
        }

        int answer_id = return_new_id_for_new_answer(question_id);
        if (answer_id <= 0)
        {
            cout << "invalid answer id\n";
            return false;
        }

        file_handler << "\n" << question_id << " " << user_id << " " << answer_id << " " << answer;
        file_handler.close();
        cout << "Your answer added, Thank you!\n";
        return true;
    }

    void delete_answer(int question_id, int user_id)
    {
        fstream reader;
        reader.open(answers_path);

        if (reader.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        vector <string>lines;

        string line;
        while (getline(reader, line))
        {
            int current_user_id = extract_user_id_from_question_or_answer_file(line);
            if (extract_question_id(line) == question_id && current_user_id == user_id) continue;

            lines.push_back(line);
        }

        reader.close();

        ofstream writer;

        writer.open(answers_path);

        if (writer.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        for (size_t i = 0; i < lines.size(); i++)
            writer << lines[i] << "\n";
        // update_all_question_and_answer_ids(question_id, user_id);
        //here i want to write a function that updates answer ids
    }

    void delete_all_answers_that_related_to_question(int question_id)
    {
        fstream reader;
        reader.open(answers_path);

        if (reader.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        vector <string>lines;

        string line;
        while (getline(reader, line))
        {
            if (extract_question_id(line) != question_id)
                lines.push_back(line);
        }

        reader.close();

        ofstream writer;

        writer.open(answers_path);

        if (writer.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        for (size_t i = 0; i < lines.size(); i++)
            writer << lines[i] << "\n";
    }

    void delete_question(int question_id)
    {
        fstream reader;
        reader.open(questions_path);

        if (reader.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        vector <string>lines;

        string line;
        while (getline(reader, line))
        {
            if (extract_question_id(line) != question_id)
                lines.push_back(line);
        }

        reader.close();

        ofstream writer;

        writer.open(questions_path);

        if (writer.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        for (size_t i = 0; i < lines.size(); i++)
            writer << lines[i] << "\n";

        delete_all_answers_that_related_to_question(question_id);
        update_question_ids(question_id);
    }

    //this function update them in two files (questions & answers)
    void update_question_ids(int question_id)
    {
        //update questions file
        fstream reader;
        reader.open(questions_path);

        if (reader.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        vector <string>questions;
        vector <int>user_ids_;
        vector <int>question_ids_;
        string line;
        while (getline(reader, line))
        {
            questions.push_back(extract_question_by_id(extract_question_id(line)));
            user_ids_.push_back(extract_user_id_from_question_or_answer_file(line));
            question_ids_.push_back(extract_question_id(line));
        }

        reader.close();

        ofstream writer;

        writer.open(questions_path);

        if (writer.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        int current_id = question_id;
        for (size_t i = 0; i < question_ids_.size(); i++)
        {
            if (i + 1 == question_id) continue;

            if (i + 1 < question_id)
            {
                writer << question_ids_[i] << " " << user_ids_[i] << " " << questions[i] << "\n";
                continue;
            }

            writer << current_id << " " << user_ids_[i] << " " << questions[i] << "\n";
            current_id++;
        }
        writer.close();
    }

    // void update_answer_ids_for_deleted_question(int question_id, int user_id)
    // {
    //     fstream reader;
    //     reader.open(answers_path);

    //     if (reader.fail())
    //     {
    //         cout << "Failed to open questions file!\n";
    //         return;
    //     }

    //     vector <string>answers;
    //     vector <int>user_ids_;
    //     vector <int>question_ids_;
    //     string line;
    //     while (getline(reader, line))
    //     {
    //         answers.push_back(extract_question_by_id(extract_question_id(line)));
    //         user_ids_.push_back(extract_user_id_from_question_or_answer_file(line));
    //         question_ids_.push_back(extract_question_id(line));
    //     }

    //     reader.close();

    //     ofstream writer;

    //     writer.open(answers_path);

    //     if (writer.fail())
    //     {
    //         cout << "Failed to open questions file!\n";
    //         return;
    //     }

    //     int current_id = question_id;
    //     for (size_t i = 0; i < question_ids_.size(); i++)
    //     {
    //         if (i + 1 == question_id) continue;

    //         if (i + 1 < question_id)
    //         {
    //             writer << question_ids_[i] << " " << user_ids_[i] << " " << answers[i] << "\n";
    //             continue;
    //         }

    //         writer << current_id << " " << user_ids_[i] << " " << answers[i] << "\n";
    //         current_id++;
    //     }
    //     writer.close();
    // }

    void update_all_answer_ids(int question_id, int user_id)
    {
        //     //update questions file
        //     fstream reader;
        //     reader.open(questions_path);

        //     if (reader.fail())
        //     {
        //         cout << "Failed to open questions file!\n";
        //         return;
        //     }

        //     vector <string>questions;
        //     vector <int>user_ids_;
        //     vector <int>question_ids_;
        //     string line;
        //     while (getline(reader, line))
        //     {
        //         questions.push_back(extract_question_by_id(extract_question_id(line)));
        //         user_ids_.push_back(extract_user_id_from_question_or_answer_file(line));
        //         question_ids_.push_back(extract_question_id(line));
        //     }

        //     reader.close();

        //     ofstream writer;

        //     writer.open(questions_path);

        //     if (writer.fail())
        //     {
        //         cout << "Failed to open questions file!\n";
        //         return;
        //     }

        //     int current_id = question_id;
        //     for (size_t i = 0; i < question_ids_.size(); i++)
        //     {
        //         if (i + 1 == question_id) continue;

        //         if (i + 1 < question_id)
        //         {
        //             writer << question_ids_[i] << " " << user_ids_[i] << " " << questions[i] << "\n";
        //             continue;
        //         }

        //         writer << current_id << " " << user_ids_[i] << " " << questions[i] << "\n";
        //         current_id++;
        //     }
        // writer.close();
    }

    void ask_question(int user_id)
    {
        fstream reader;
        reader.open(questions_path);

        if (reader.fail())
        {
            cout << "Failed to open questions file!\n";
            return;
        }

        string line;
        int last_id = 0;
        while (getline(reader, line))
            last_id = extract_question_id(line);

        fstream file_handler(questions_path.c_str(), ios::app);
        if (file_handler.fail())
        {
            cout << "Failed to open signed up users file\n";
            return;
        }

        string question_content;
        cout << "Ask a question:\n";
        getline(cin, question_content);

        file_handler << "\n" << last_id + 1 << " " << user_id << " " << question_content;
        cout << "You question added successfully\n";
    }
};

struct general_struct
{
    int total_users, total_questions;
    user users_;
    question questions_;
    // question questions[MAX_GENERAL_QUESTIONS];

    void login()
    {
        users_.login();
        users_.update_login_users_ids_vector();
    }

    void logout(int trials = 3)
    {
        if (trials == 0)
        {
            cout << "Failed to sign out, Try later.\n";
            return;
        }

        bool done = users_.logout();
        if (done)
        {
            users_.update_login_users_ids_vector();
            cout << "You log out successfully\n";
            return;
        }

        return logout(trials - 1);
    }

    void sign_up()
    {
        users_.sign_up();
        users_.update_signed_in_users_ids_vector();
    }

    void sign_out(int trials = 3)
    {
        if (trials == 0)
        {
            cout << "Failed to sign out, Try later.\n";
            return;
        }

        bool done = users_.sign_out();
        cout << done << "\n";

        if (done) {
            users_.update_signed_in_users_ids_vector();
            cout << "You signed out successfully\n";
            return;
        }
        return sign_out(trials - 1);
    }

    int Menu_1()
    {
        int choice;
        cout << "Menu:\n";
        cout << "\t 1) Login\n";
        cout << "\t 2) Sign Up\n";
        cout << "Enter your choice (1,2)\n";
        cin >> choice;

        if (choice > 2 || choice < 1) return Menu_1();
        return choice;
    }

    int Menu_2()
    {
        int choice;
        cout << "Menu:\n";
        cout << "\t 1) Print Questions to me\n";
        cout << "\t 2) Print Questions from me\n";
        cout << "\t 3) Answer Question\n";
        cout << "\t 4) Delete Question\n";
        cout << "\t 5) Ask Question\n";
        cout << "\t 6) List System Users\n";
        cout << "\t 7) Feed\n"; //list feeds for all questions
        cout << "\t 8) Logout\n";
        cout << "\t 9) Sing Out\n";
        cout << "Enter your choice (1,9)\n";
        cin >> choice;

        if (choice > 9 || choice < 1) return Menu_2();
        return choice;
    }

    void run_1()
    {
        int choice = Menu_1();

        if (choice == 1) login();
        if (choice == 2) sign_up();

        Menu_2();
    }

    void run_2()
    {
        int choice = Menu_2();

        if (choice == 1) print_questions_to_user();
    }

    void print_questions_to_user()
    {

    }

    void answer_question()
    {
        int question_id, user_id;
        cout << "Enter question id that you want to answer, Enter -1 to cancel\n";
        cin >> question_id;

        cout << "Enter your id:\n";
        cin >> user_id;

        bool user_login = users_.check_if_user_login_by_id(user_id);

        if (!user_login)
        {
            cout << "You are not login, login then try agin\n";
            return;
        }

        if (question_id == -1) return;

        if (question_id < 0)
        {
            cout << "Invalid Question id\n";
            return answer_question();
        }

        string question_content = questions_.extract_question_by_id(question_id);

        if (question_content == "Error")
        {
            cout << "This question doesn't exists, Try again\n";
            return answer_question();
        }

        questions_.answer_question(question_id, user_id);
    }

    void delete_question()
    {
        int user_id;
        cout << "Enter your id:\n";
        cin >> user_id;

        if (!users_.check_if_user_login_by_id(user_id))
        {
            cout << "You are not login!, Login then try again!\n";
            return;
        }

        int question_id;
        cout << "Enter question id:\n";
        cin >> question_id;

        if (!questions_.check_if_question_belongs_to_user(question_id, user_id))
        {
            cout << "You are not the owner of this question, you can't delete it\n";
            return;
        }

        questions_.delete_question(question_id);
    }
};

int main()
{
    user user_;
    general_struct gen_;
    question question_;

    // cout << user_.sign_up();
    // cout << return_file_lines_number(signed_up_users_path);
    // cout << question_.extract_answer_id_from_line("9 3 1 Numbers that, when multiplied by themselves, result in a negative number. They are crucial for advanced math and physics.");
    // cout << question_.return_new_id_for_new_answer(24);
    // cout << question_.answer_question(25, 2);

    // question_.delete_question(17);
    // question_.delete_all_answers_that_related_to_question(22);
    // question_.delete_answer(25, 2);

    // question_.ask_question(3);
    // user_.list_system_users();
    // cout << convert_char_to_signed_integer('7');
    user_.update_login_users_ids_vector();

    user_.print_vector();

    return 0;
}