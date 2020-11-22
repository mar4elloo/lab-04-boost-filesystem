// Copyright 2020 Your Name <your_email>

#include <header.hpp>

int main(int argc, char* argv[]) {
    filesys::path the_path_to_ftp;
    if (argc >= 2) {
        the_path_to_ftp = argv[1];
    } else {
        the_path_to_ftp = filesys::current_path();
    }
    std::map<std::string, std::set<The_class_of_the_account>> the_brokers =
            the_mainlist_of_brokers_accounts(the_path_to_ftp);
    the_information_of_brokers(the_path_to_ftp, std::cout);
    for (auto& a_broker : the_brokers) {
        for (auto& an_account_of_a_broker : a_broker.second) {
            std::cout << "broker:" << a_broker.first
                      << " account:";
            std::cout.fill('0');
            std::cout.width(8);
            std::cout << an_account_of_a_broker.get_the_id_of_the_broker();
            std::cout << " files:" <<
                      an_account_of_a_broker.get_the_number_of_files()
                      << " lastdate:" <<
                      an_account_of_a_broker.get_the_latest_date() <<
                      std::endl;
        }
    }
    return 0;
}