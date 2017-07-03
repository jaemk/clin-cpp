#include <libnotify/notify.h>
#include <cstring>
#include <iostream>


bool should_help(int argc, char* argv[]) {
    if (argc == 1)
        return true;

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
            return true;
        }
    }
    return false;
}


void show_help() {
    std::string text =
"** clin: cli-notify **\n\n"
" clin [command] [notification-message]\n"
" ex. clin 'echo hello!' 'Done echoing!'\n";
    std::cout << text;
}


int main(int argc, char* argv[]) {
    if (should_help(argc, argv)) {
        show_help();
        return 0;
    }

    if (argc != 3) {
        std::cout << "[ERROR]: Please specify a command and message!" << std::endl;
        show_help();
        return -1;
    }

    std::string command = argv[1];
    std::string message = argv[2];
    int ret = system(command.c_str());
    if (ret != 0)
        message = "[ERRORED]: " + message;

    notify_init("Notify!");
    NotifyNotification* n = notify_notification_new("CLIN: Command-line Notification", message.c_str(), 0);
    notify_notification_set_timeout(n, 5000);

    if (!notify_notification_show(n, 0)) {
        std::cerr << "notification failed" << std::endl;
        return -1;
    }
    return 0;
}
