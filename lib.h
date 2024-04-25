#ifndef LIB_H_
#define LIB_H_
#include<iostream>
// #include<string>
#include<bits/stdc++.h>
using namespace std;

extern const int MAX_USERS,
MAX_GENERAL_QUESTIONS,
MAX_SUB_QUESTIONS;

extern const string signed_up_users_path,
current_login_users_path,
questions_path,
answers_path;

string convert_int_to_string(int num);

int convert_char_to_signed_integer(char ch);

bool is_symbol(char ch);

int convert_string_to_integer(string str);

int extract_id_from_line(string line);

string extract_email_from_line(string file_line);

string extract_password_from_sign_up_file(string file_line);

string extract_name_from_line(string line);

string replace_texts_in_the_line(string line, string old_text, string new_text);

int return_file_lines_number(string file_path);

int extract_question_id(string line);

int extract_user_id_from_question_or_answer_file(string line);

#endif