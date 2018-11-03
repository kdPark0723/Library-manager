#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>
#include <time.h>

/*  Screen type define
 *
 *  If you want add new screen, try following steps.
 *  1. Add new define for new screen.
 *  2. Change other define, all define should have another number.
 *  3. Change SCREEN_MAX.
 *  4. Add new screen's function(draw_~~_screen, input_~~_screen).
 *  5. Link screen and function(it is in the init_screens function).
 */
#define SCREEN_INIT 0
#define SCREEN_SIGN_UP 1
#define SCREEN_SIGN_IN 2
#define SCREEN_MENU_MEMBER 3
#define SCREEN_MENU_ADMIN 4
#define SCREEN_MAX 5

/*  String size define
 */
#define SIZE_STUDENT_NUMBER 8
#define SIZE_PHONE_NUMBER 13

#define SIZE_BOOK_NUMBER 7
#define SIZE_ISBN 13

struct _LinkedList
{
    void *contents;
    struct _LinkedList *next;
};
typedef struct _LinkedList LinkedList;

typedef struct Client
{
    wchar_t student_number[SIZE_STUDENT_NUMBER+1];
    wchar_t phone_number[SIZE_PHONE_NUMBER+1];
    wchar_t *password;
    wchar_t *name;
    wchar_t *address;
} Client;

typedef struct Book
{
    wchar_t number[SIZE_BOOK_NUMBER+1];
    wchar_t ISBN[SIZE_ISBN+1];
    wchar_t availability;
    wchar_t *name;
    wchar_t *publisher;
    wchar_t *author;
    wchar_t *location;
} Book;

typedef struct Borrow
{
    wchar_t student_number[SIZE_STUDENT_NUMBER+1];
    wchar_t book_number[SIZE_BOOK_NUMBER+1];
    time_t loan_date;
    time_t return_date;
} Borrow;

struct Screens;

typedef struct Data
{
    LinkedList *clients, *books, *borrows;
    struct Screens* screens;
    Client* login_client;
    _Bool is_running;
} Data;

typedef struct Screen
{
    char type;
    void (*draw)(Data const *);
    void (*input)(const wchar_t const *, Data const *);
} Screen;

typedef struct Screens
{
    Screen screens[SCREEN_MAX];
    char type;
} Screens;

/*  @brief Init client list.
 *
 *  Get client data for file and allocate client and link the list.
 *
 *  @param file_name The file name to get data.
 *  @return LinkedList* Allocated and sorted linked list.
 */
LinkedList *init_clients(const char const *file_name);
/*  @brief Init book list.
 *
 *  Get book data for file and allocate book and link the list.
 *
 *  @param file_name The file name to get data.
 *  @return LinkedList* Allocated and sorted linked list.
 */
LinkedList *init_books(const char const *file_name);
/*  @brief Init borrow list.
 *
 *  Get borrow data for file and allocate borrow and link the list.
 *
 *  @param file_name The file name to get data.
 *  @return LinkedList* Allocated and sorted linked list.
 */
LinkedList *init_borrows(const char const *file_name);

/*  @brief Create book.
 *
 *  Create book by ISBN, publisher, author, location and name.
 *  Book's number and availability are specified in this function.
 *
 *  @param name The book's name.
 *  @param publisher The book's publisher.
 *  @param author The book's author.
 *  @param ISBN The book's ISBN.
 *  @param location The book's location.
 *  @return Borrow* new borrow made by datas.
 */
Borrow *create_book(wchar_t *name, wchar_t *publisher, wchar_t *author, wchar_t *ISBN, wchar_t *location);
/*  @brief Create borrow.
 *
 *  Create borrow by client and book.
 *
 *  @param client The client to borrow.
 *  @param book The book to borrow.
 *  @return Borrow* new borrow made by client and book.
 */
Borrow *create_borrow(Client const *client, Book const *book);

/*  @brief Print client.
 *
 *  Print client data.
 *
 *  @param client Client pointer to print.
 *  @return void.
 */
void print_client(const Client const *client);
/*  @brief Print book.
 *
 *  Print book data.
 *
 *  @param book Book pointer to print.
 *  @return void.
 */
void print_book(const Book const *book);
/*  @brief Print borrow.
 *
 *  Print borrow data.
 *
 *  @param borrow Borrow pointer to print.
 *  @return void.
 */
void print_borrow(const Borrow const *borrow);

/*  @brief Print All clients.
 *
 *  Print all clients data using linked list.
 *
 *  @param client_list Lined list to print.
 *  @return void.
 */
void print_clients(const LinkedList const *client_list);
/*  @brief Print All books.
 *
 *  Print all books data using linked list.
 *
 *  @param book_list Lined list to print.
 *  @return void.
 */
void print_books(const LinkedList const *book_list);
/*  @brief Print All borrows.
 *
 *  Print all borrows data using linked list.
 *
 *  @param borrow_list Linked list to print.
 *  @return void.
 */
void print_borrows(const LinkedList const *borrow_list);

/*  @brief Save clients to file.
 *
 *  Save clients to file.
 *  All clients should be sorted and data in file also should be sorted.
 *
 *  @param client_list Linked list to save.
 *  @param file_name File name to save.
 *  @return void.
 */
void save_clients(const LinkedList const *client_list, const char const *file_name);
/*  @brief Save books to file.
 *
 *  Save books to file.
 *  All books should be sorted and data in file also should be sorted.
 *
 *  @param book_list Linked list to save.
 *  @param file_name File name to save.
 *  @return void.
 */
void save_books(const LinkedList const *book_list, const char const *file_name);
/*  @brief Save borrows to file.
 *
 *  Save borrows to file.
 *  All borrows should be sorted and data in file also should be sorted.
 *
 *  @param borrow_list Linked list to save.
 *  @param file_name File name to save.
 *  @return void.
 */
void save_borrows(const LinkedList const *borrow_list, const char const *file_name);

/*  @brief Insert client in the linked list.
 *
 *  Fined the current position in linked list.
 *  Create new node and add to the list.
 *  All times list should be sorted.
 *
 *  @param client_list Linked list.
 *  @param client Client to insert.
 *  @return LinkedList* Linked list's first member.
 */
LinkedList *insert_client(LinkedList const *client_list, const Client const *client);
/*  @brief Insert client in the linked list.
 *
 *  Fined the current position in linked list.
 *  Create new node and add to the list.
 *  All times list should be sorted.
 *
 *  @param client_list Linked list.
 *  @param client Client to insert.
 *  @return LinkedList* Linked list's first member.
 */
LinkedList *insert_book(LinkedList const *book_list, const Book const book);
/*  @brief Insert client in the linked list.
 *
 *  Fined the current position in linked list.
 *  Create new node and add to the list.
 *  All times list should be sorted.
 *
 *  @param client_list Linked list.
 *  @param client Client to insert.
 *  @return LinkedList* Linked list's first member.
 */
LinkedList *insert_borrow(LinkedList const *borrow_list, const Borrow const *borrow);

/*  @brief Find client by name.
 *
 *  Find client by name.
 *
 *  @param client_list The client list to get client.
 *  @param student_number The client's student number.
 *  @return Client* Fined client.
 */
Client *find_client_by_student_number(const LinkedList const *client_list, const char const *student_number);
/*  @brief Find books by name.
 *
 *  Find book by name.
 *
 *  @param book_list The book list to get book.
 *  @param book_name The book name.
 *  @return LinkedList* Fined Book.
 */
LinkedList *find_books_by_name(const LinkedList const *book_list, const char const *book_name);
/*  @brief Find books by name.
 *
 *  Find book by name.
 *
 *  @param book_list The book list to get book.
 *  @param book_ISBN The book ISBN.
 *  @return LinkedList* Fined Book list.
 */
LinkedList *find_books_by_ISBN(const LinkedList const *book_list, const char const *book_ISBN);
/*  @brief Find books by number.
 *
 *  Find book by name.
 *
 *  @param book_list The book list to get book.
 *  @param book_number The book's number.
 *  @return Book* Fined Book list.
 */
Book *find_book_by_number(const LinkedList const *book_list, const char const *book_number);
/*  @brief Find borrow by number.
 *
 *  Find borrow by client and book.
 *
 *  @param book_list The book list to get book.
 *  @param book_number The book's number.
 *  @return Book* Fined Book list.
 */
Borrow *find_borrow(Client const *client, Book const *book);

/*  @brief remove client to client list.
 *
 *  Find client and remove the list.
 *  Free client, unused list memory.
 *
 *  @param client_list The client list to remove client.
 *  @param client The client will be removed.
 *  @return void.
 */
void remove_client(LinkedList const *client_list, Client const *client);
/*  @brief remove book to book list.
 *
 *  Find book and remove the list.
 *  Free book, unused list memory.
 *
 *  @param book_list The book list to remove book.
 *  @param book The book will be removed.
 *  @return void.
 */
void remove_book(LinkedList const *book_list, Book const *book);
/*  @brief remove borrow to borrow list.
 *
 *  Find borrow and remove the list.
 *  Free borrow, unused list memory.
 *
 *  @param borrow_list The borrow list to remove borrow.
 *  @param borrow The borrow will be removed.
 *  @return void.
 */
void remove_borrow(LinkedList const *borrow_list, Borrow const *borrow);

/*  @brief Free memory for list.
 *
 *  Free momory for list but, It isn't free list's member.
 *
 *  @param list Linked list to free memory.
 *  @return void.
 */
void destory_list(LinkedList *list);

/*  @brief Destory client list.
 *
 *  Save client data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param client_list Linked list, it have client data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destory_clients(LinkedList *client_list, const char const *file_name);
/*  @brief Destory book list.
 *
 *  Save book data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param book_list Linked list, it have book data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destory_books(LinkedList *book_list, const char const *file_name);
/*  @brief Destory borrow list.
 *
 *  Save borrow data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param borrow_list Linked list, it have borrow data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destory_borrows(LinkedList *borrow_list, const char const *file_name);

/*  @brief Destory client.
 *
 *  Free client's member
 *  Free client
 *
 *  @param client Client to free.
 *  @return void.
 */
void destory_client(Client const *client);
/*  @brief Destory book.
 *
 *  Free book's member
 *  Free book
 *
 *  @param book Book to free.
 *  @return void.
 */
void destory_book(Book const *book);
/*  @brief Destory borrow.
 *
 *  Free borrow's member
 *  Free borrow
 *
 *  @param borrow Borrow to free.
 *  @return void.
 */
void destory_borrow(Borrow const *borrow);

/*  @brief Init screens.
 *
 *  Allocate memory for screens.
 *  Set screen's type.
 *  Link screen's function pointer.
 *  Init type to init screen.
 *
 *  @param void.
 *  @return Screens* Initaled screens.
 */
Screens *init_screens(void);
/*  @brief Change screen.
 *
 *  Change screens's type
 *
 *  @param type The type to change.
 *  @return void.
 */
void change_screen(char type);
/*  @brief Clear screen.
 *
 *  Clear screen.
 *
 *  @param void.
 *  @return void.
 */
void clear_screen(void);
/*  @brief Draw screen.
 *
 *  Fine current screen by type.
 *  Call draw function linked current screen.
 *
 *  @param screens screen data.
 *  @param data program's all data.
 *  @return void.
 */
void draw_screen(Screens const *screens, Data const *data);
/*  @brief Get input data and call current function.
 *
 *  Fine current screen by type.
 *  Call input function linked current screen.
 *
 *  @param screens screen data.
 *  @param data program's all data.
 *  @return void.
 */
void input_screen(Screens *screens, Data *data);
/*  @brief Destory screens.
 *
 *  Free memory to screens.
 *
 *  @param screens screen data.
 *  @return void.
 */
void destory_screens(Screens *screens);

/*  @brief Draw init screen.
 *
 *  Draw init screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_init_screen(Data const *data);
/*  @brief Process init screen's input data.
 *
 *  Process init screen's input data.
 *
 *  @param input input string.
 *  @param data program's all data.
 *  @return void.
 */
void input_init_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw sign up screen.
 *
 *  Draw sign up screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_sign_up_screen(Data const *data);
/*  @brief Process sign up screen's input data.
 *
 *  Process sign up screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_sign_up_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw sign in screen.
 *
 *  Draw sign in screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_sign_in_screen(Data const *data);
/*  @brief Process sign in screen's input data.
 *
 *  Process sign in screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_sign_in_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw menu member screen.
 *
 *  Draw menu member screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_menu_member_screen(Data const *data);
/*  @brief Process menu member screen's input data.
 *
 *  Process menu member screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_menu_member_screen(const wchar_t const *input, Data const *data);

/*  @brief Draw menu admin screen.
 *
 *  Draw menu admin screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_menu_admin_screen(Data const *data);
/*  @brief Process menu admin screen's input data.
 *
 *  Process menu admin screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_menu_admin_screen(const wchar_t const *input, Data const *data);

/*   @prog Library manager
 *
 *   Library manager program for programming team project
 *  1. Init datas.
 *  2. Clear screen.
 *  3. Draw screen.
 *  4. Get input string and processing.
 *  5. If program is running, go to step 2.
 *  6. Save all data and free the memory.
 *  7. End the program.
 *
 *   @author Park Si-Yual.
 *  @recent 2018-11-03.
 */
int main(void)
{
    Data data;

    data.clients = init_clients("client");
    data.books = init_books("book");
    data.borrows = init_borrows("borrow");

    data.screens = init_screens();

    data.is_running = 1;
    while (data.is_running) {
        clear_screen();
        draw_screen(data.screens, &data);
        input_screen(data.screens, &data);
    }

    destory_clients(data.clients, "client");
    destory_books(data.books, "book");
    destory_borrows(data.borrows, "borrow");

    destory_screens(data.screens);

    return 0;
}
