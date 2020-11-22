// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/filesystem.hpp>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <regex>
#include <utility>

namespace filesys = ::boost::filesystem;

class The_class_of_the_account {
public:
    The_class_of_the_account(const unsigned int& new_account, const unsigned int& new_date);
    The_class_of_the_account(const unsigned int& new_account, const unsigned int& new_date, const size_t& new_files);
    void update_the_information_of_the_account(const unsigned int& new_date, const size_t& new_number);
    bool operator<(const The_class_of_the_account& new_account) const;
    bool operator==(const The_class_of_the_account& new_account) const;
    bool operator!=(const The_class_of_the_account& new_account) const;
    unsigned int get_the_id_of_the_broker() const;
    unsigned int get_the_latest_date() const;
    size_t get_the_number_of_files() const;
private:
    unsigned int the_account_of_the_broker;
    size_t the_number_of_files = 0;
    unsigned int the_latest_date;
};

std::map<std::string, std::set<The_class_of_the_account>> the_mainlist_of_brokers_accounts(const filesys::path& new_path);
void the_information_of_brokers(const filesys::path& new_path, std::ostream& new_outstream);
std::pair<std::set<The_class_of_the_account>, std::set<std::string>> the_lists_of_brokers_accounts(const filesys::path& new_path);
bool check_if_data_is_correct(const std::string& new_date);

#endif  // INCLUDE_HEADER_HPP_