Apply the command g++ project_ask_fm_Q\&A.cpp lib.cpp to run the program

Users guide:
-you can ask questions and answer to another users questions but you must be login to the system
-many users can answer the same question and even the same user can answer the same questions many times
-when you delete your question all answers for your question will be deleted

Program structure explanation:
\*ordered in this way

1. questions.txt data:
   question_id (id > 0) | user_id (who asked) | question

2. answers.txt:
   question_id (which the answer belongs to) | user_id (who answered this question) | answer_id | answer

\*NOTE: we need answer id because many users can answer the same question, even the same user can do that
so we need id for each answer

\*NOTE: ids are not unique for different questions BUT they are unique for the same question
