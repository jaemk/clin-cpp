#include <libnotify/notify.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>


struct Args {
    bool help = false;
    std::string command = "";
    std::string message = "";
};


template<typename ... T>
bool arg_in(const char* argument, const T&... _opts) {
    std::vector<std::string> opts = {_opts...};
    for (auto opt : opts) {
        if (std::strcmp(argument, opt.c_str()) == 0)
            return true;
    }
    return false;
}


Args parse_args(int argc, char* argv[]) {
    Args args;
    if (argc == 1) {
        args.help = true;
        return args;
    }

    for (int i = 1; i < argc; i++) {
        const char* _arg = argv[i];
        if (arg_in(_arg, "--help", "-h")) {
            args.help = true;
            return args;
        } else if (i == 1) {
            args.command = _arg;
        } else if (i == 2) {
            args.message = _arg;
        }
    }

    return args;
}


void show_help() {
    std::string text =
"CLIN (cli-notify) 0.1\n"
"James K. <james.kominick@gmail.com>\n"
"Command Completion Notifications\n"
"\n"
"USAGE:\n"
"    clin [-h, --help] command [notification-message]\n"
"\n"
"FLAGS:\n"
"    -h, --help: Prints help information\n"
"";
    std::cout << text;
}


int main(int argc, char* argv[]) {
    Args args = parse_args(argc, argv);

    if (args.help) {
        show_help();
        return 0;
    }

    if (args.message.empty())
        args.message = args.command;

    int ret = system(args.command.c_str());
    if (ret != 0) {
        std::stringstream s;
        s << "[ERROR: " << ret << "]: " << args.message;
        args.message = s.str();
    }

    notify_init("Notify!");
    NotifyNotification* n = notify_notification_new("CLIN:", args.message.c_str(), 0);
    notify_notification_set_timeout(n, 5000);

    if (!notify_notification_show(n, 0)) {
        std::cerr << "[ERROR]: notification failed" << std::endl;
        return -1;
    }
    return 0;
}
