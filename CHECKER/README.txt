*******************************
    Topic E - Checker usage
*******************************


FILE
    File list: CHECKER, case_1.enc, case_2.enc, README

    ** This checker can run on CIC machine only **
    ** Please check whether "case_1.enc" and "case_2.enc" have been put in current directory before running checker. **


USAGE
    ./CHECKER [Result file] [Case number]


EXAMPLE
    ./CHECKER  case_1_result  1
    ./CHECKER  case_2_result  2


LOG MESSAGES
    If all of output result are correct, checker will show "ALL PASS!". Or checker will display the error message for your result.
    Because checker will sort your result with coordinate at first. If there exists error rectangle, checker will show the next correct result rectangle only.
