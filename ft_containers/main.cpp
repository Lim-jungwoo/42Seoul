#include "container/stack.hpp"
#include "container/map.hpp"
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <iomanip>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

void	test_insert_single()
{
	std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (single element) "
              << "] --------------------]\t\t\033[0m";
    {
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        ft::vector<std::string>::iterator ft_it;
        std::vector<std::string>::iterator it;
        /*
         * bool to store the comparison
         */
        bool cond = true;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            it = v.insert(v.begin(), "hello");
			// exit(1);
            ft_it = ft_v.insert(ft_v.begin(), "hello");
            ft_it->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
			
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (*ft_it == *it));
			
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;

            it = v.insert(v.end(), "hello");
            ft_it = ft_v.insert(ft_v.end(), "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(30);
            ft_v.reserve(30);
            valid_it = ft_v.begin();
            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
}

int	main(void)
{
	test_insert_single();
}