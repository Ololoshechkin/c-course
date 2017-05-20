//
// Created by Vadim on 02.05.17.
//

#include "exceptions.h"

const char* argument_exeption::what() const throw() 
{
	return message.c_str();
}

illegal_argument_cnt_exception::illegal_argument_cnt_exception(int arg_cnt, int expected_arg_cnt)
{
	message = "unexpected arguments count. expected : " + std::to_string(expected_arg_cnt) +
	          " , but found : " + std::to_string(arg_cnt);
}

illegal_arguments_exception::illegal_arguments_exception(int arg_number, std::string expected_arg) 
{
	message = "instead of " + std::to_string(arg_number) + "-th parametr expected " + expected_arg;
}

const char* bad_file_format_exception::what() const throw() 
{
	return "bad decrypting file format";
}