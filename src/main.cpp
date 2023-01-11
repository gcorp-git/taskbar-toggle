#include "app.cpp"
#include "utils.cpp"

int main() {
    if (isDuplicateProcess()) return EXIT_SUCCESS;

    auto app = new Taskbar::App();

    app->start();

    auto status = app->getStatus();
    
    if (status.error) status.show();

    return !status.error ? EXIT_SUCCESS : EXIT_FAILURE;
}
