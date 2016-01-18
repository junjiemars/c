int main(int argc, const char *argv[]) {
    int i = 0x11223344;
    char *p = (char *)&i;

    if (0x44 == *p)
        return 0;
    return 1;
}
