#include <cstdlib>

int main(int argc, char *argv[])
{
    system("dbus-launch gnome-terminal -- \"./database-node\"");
    system("dbus-launch gnome-terminal -- \"./server-node\"");
    system("dbus-launch gnome-terminal -- \"./requestor-node\"");
}
