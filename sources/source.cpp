// Copyright 2020 Artamonov Mark <a.mark.2001@mail.ru>

#include <header.hpp>

The_class_of_the_account::The_class_of_the_account(const unsigned int& new_account,
                                                   const unsigned int& new_date){
    the_latest_date = new_date;
    the_account_of_the_broker = new_account;
    the_number_of_files = 1;
}

The_class_of_the_account::The_class_of_the_account(const unsigned int& new_account,
                                                   const unsigned int& new_date, const size_t& new_files){
    the_latest_date = new_date;
    the_account_of_the_broker = new_account;
    the_number_of_files = new_files;
}

void The_class_of_the_account::update_the_information_of_the_account(const unsigned int& new_date,
                                                                     const size_t& new_number) {
    if (new_number > the_number_of_files){
        the_number_of_files = new_number;
    }
    if (new_date > the_latest_date){
        the_latest_date = new_date;
    }
    ++the_number_of_files;
}

bool The_class_of_the_account::operator==(const The_class_of_the_account& new_account) const {
    return
    the_account_of_the_broker == new_account.the_account_of_the_broker &&
    the_number_of_files == new_account.the_number_of_files &&
    the_latest_date == new_account.get_the_latest_date();
}

bool The_class_of_the_account::operator!=(const The_class_of_the_account& new_account) const {
    return
    the_account_of_the_broker != new_account.the_account_of_the_broker;
}

bool The_class_of_the_account::operator<(const The_class_of_the_account& new_account) const {
    return
    the_account_of_the_broker < new_account.the_account_of_the_broker;
}

unsigned int The_class_of_the_account::get_the_latest_date() const {
    return the_latest_date;
}

size_t The_class_of_the_account::get_the_number_of_files() const {
    return the_number_of_files;
}

unsigned int The_class_of_the_account::get_the_id_of_the_broker() const {
    return the_account_of_the_broker;
}

std::map<std::string, std::set<The_class_of_the_account>> the_mainlist_of_brokers_accounts(
        const filesys::path& new_path) {
    std::map<std::string, std::set<The_class_of_the_account>> the_information;
    for (const auto& the_entry_to_directory :
    filesys::directory_iterator(new_path)) {
        if (!filesys::is_directory(the_entry_to_directory)){
            continue;
        }
        const auto& the_entry_to_the_path = the_entry_to_directory.path();
        auto the_name_of_entry = the_entry_to_the_path.filename().string();
        the_information.insert(
                std::make_pair(the_name_of_entry,
                        the_lists_of_brokers_accounts(the_entry_to_the_path).first));
    }
    return the_information;
}

void the_information_of_brokers(const filesys::path& new_path,
        std::ostream& new_outstream) {
    for (const auto& the_entry_to_directory :
    filesys::directory_iterator(new_path)) {
        if (!filesys::is_directory(the_entry_to_directory)) {
            continue;
        }
        std::set<std::string> the_accounts_list =
                the_lists_of_brokers_accounts(the_entry_to_directory).second;
        for (auto& an_account : the_accounts_list) {
            new_outstream << an_account;
        }
    }
}

std::pair<std::set<The_class_of_the_account>, std::set<std::string>> the_lists_of_brokers_accounts(
        const filesys::path& new_path) {
    const std::regex the_template_of_filename("^balance_(\\d{8})_(\\d{8}).txt$");
    std::set<The_class_of_the_account> the_set_of_the_accounts;
    std::set<std::string> the_list_of_the_accounts;
    for (const auto& the_entry_of_the_file :
    filesys::directory_iterator(new_path)) {
        filesys::path the_entry_to_the_path;
        if (filesys::is_regular_file(the_entry_of_the_file)) {
            the_entry_to_the_path = the_entry_of_the_file.path();
        }
        else if (filesys::is_symlink(the_entry_of_the_file)){
            the_entry_to_the_path =
                    filesys::read_symlink(the_entry_of_the_file.path());
        }
        std::string the_name_of_the_file = the_entry_to_the_path.filename().string();
        if (!std::regex_match(the_name_of_the_file, the_template_of_filename)) {
            continue;
        }
        std::smatch the_match;
        std::regex_search(the_name_of_the_file,
                the_match, the_template_of_filename);
        if (!check_if_data_is_correct(the_match[2])) {
            continue;
        }
        The_class_of_the_account an_account(std::stoi(the_match[1]),
                                            std::stoi(the_match[2]));
        auto the_accounts_iter = the_set_of_the_accounts.find(an_account);
        if (the_accounts_iter == the_set_of_the_accounts.end()) {
            the_set_of_the_accounts.insert(an_account);
        }
        else {
            auto& one_element = *the_accounts_iter;
            an_account.update_the_information_of_the_account(
                    one_element.get_the_latest_date(),
                    one_element.get_the_number_of_files());
            the_set_of_the_accounts.erase(the_accounts_iter);
            the_set_of_the_accounts.insert(an_account);
        }
        the_list_of_the_accounts.insert(
                new_path.filename().string() + " " +
                the_entry_to_the_path.filename().string() + "\n");
    }
    return std::make_pair(
            the_set_of_the_accounts, the_list_of_the_accounts);
}

bool check_if_data_is_correct(const std::string& new_date) {

    unsigned int new_day = std::stoi(
            new_date.substr(6, 2));
    unsigned int new_month = std::stoi(
            new_date.substr(4, 2));
    return
            new_day <= 31 && new_month <= 12;
}