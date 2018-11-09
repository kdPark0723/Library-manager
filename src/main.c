#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include <unistd.h>

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
#define SCREEN_FIND_BOOK 5
#define SCREEN_MAX 6

/*  String size define
 */
#define SIZE_STUDENT_NUMBER 8
#define SIZE_PHONE_NUMBER 13

#define SIZE_BOOK_NUMBER 7
#define SIZE_ISBN 13

#define SIZE_INPUT_MAX 100

/* String const
 */
#define STRING_CLIENT_FILE "client"
#define STRING_BOOK_FILE "book"
#define STRING_BORROW_FILE "borrow"

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
    wchar_t *book_name;
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
    _Bool is_admin;
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
    char pre_screen_type;
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
 *  @param book_list The book list to fine book numbet to use.
 *  @param name The book's name.
 *  @param publisher The book's publisher.
 *  @param author The book's author.
 *  @param ISBN The book's ISBN.
 *  @param location The book's location.
 *  @return Book* new Book made by datas.
 */
Book *create_book(const LinkedList const *book_list, const wchar_t const *name, const wchar_t const *publisher, const wchar_t const *author, const wchar_t const *ISBN, const wchar_t const *location);
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
LinkedList *insert_book(LinkedList const *book_list, const Book const *book);
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

/*  @brief Find client by student number.
 *
 *  Find client by student number.
 *
 *  @param client_list The client list to get client.
 *  @param student_number The client's student number.
 *  @return Client* Fined client.
 */
Client *find_client_by_student_number(const LinkedList const *client_list, const wchar_t const *student_number);
/*  @brief Find books by name.
 *
 *  Find book by name.
 *
 *  @param book_list The book list to get book.
 *  @param book_name The book name.
 *  @return LinkedList* Fined Book.
 */
LinkedList *find_books_by_name(const LinkedList const *book_list, const wchar_t const *book_name);
/*  @brief Find books by author.
 *
 *  Find book by author.
 *
 *  @param book_list The book list to get book.
 *  @param book_author The book's author.
 *  @return LinkedList* Fined Book list.
 */
LinkedList *find_books_by_author(const LinkedList const *book_list, const wchar_t const *book_author);
/*  @brief Find books by publisher.
 *
 *  Find book by publisher.
 *
 *  @param book_list The book list to get book.
 *  @param book_publisher The book's publisher.
 *  @return LinkedList* Fined Book list.
 */
LinkedList *find_books_by_publisher(const LinkedList const *book_list, const wchar_t const *book_publisher);
/*  @brief Find books by ISBN.
 *
 *  Find book by ISBN.
 *
 *  @param book_list The book list to get book.
 *  @param book_ISBN The book's ISBN.
 *  @return LinkedList* Fined Book list.
 */
LinkedList *find_books_by_ISBN(const LinkedList const *book_list, const wchar_t const *book_ISBN);
/*  @brief Find books by number.
 *
 *  Find book by number.
 *
 *  @param book_list The book list to get book.
 *  @param book_number The book's number.
 *  @return Book* Fined Book list.
 */
Book *find_book_by_number(const LinkedList const *book_list, const wchar_t const *book_number);
/*  @brief Find borrow list by client.
 *
 *   Find borrow list by client.
 *
 *  @param client The client to get borrow.
 *  @return LinkedList* Fined Borrow list.
 */
LinkedList *find_borrows_by_client(Client const *client);
/*  @brief Find borrow by client and book.
 *
 *  Find borrow by client and book.
 *
 *  @param client The client to get borrow.
 *  @param book The book to get borrow.
 *  @return Borrow* Fined Borrow.
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
void destroy_list(LinkedList *list);

/*  @brief Destroy client list.
 *
 *  Save client data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param client_list Linked list, it have client data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destroy_clients(LinkedList *client_list, const char const *file_name);
/*  @brief Destroy book list.
 *
 *  Save book data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param book_list Linked list, it have book data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destroy_books(LinkedList *book_list, const char const *file_name);
/*  @brief Destroy borrow list.
 *
 *  Save borrow data to file.
 *  Free memory to list.
 *  Data in the file is sorted.
 *
 *  @param borrow_list Linked list, it have borrow data.
 *  @param file_name Saving file name.
 *  @return void.
 */
void destroy_borrows(LinkedList *borrow_list, const char const *file_name);

/*  @brief Destroy client.
 *
 *  Free client's member
 *  Free client
 *
 *  @param client Client to free.
 *  @return void.
 */
void destroy_client(Client const *client);
/*  @brief Destroy book.
 *
 *  Free book's member
 *  Free book
 *
 *  @param book Book to free.
 *  @return void.
 */
void destroy_book(Book const *book);
/*  @brief Destroy borrow.
 *
 *  Free borrow's member
 *  Free borrow
 *
 *  @param borrow Borrow to free.
 *  @return void.
 */
void destroy_borrow(Borrow const *borrow);

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
 *  @param screens The screens to change.
 *  @param type The type to change.
 *  @return void.
 */
void change_screen(Screens const *screens, char type);
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
void input_screen(Screens *screens, Data const *data);
/*  @brief Destroy screens.
 *
 *  Free memory to screens.
 *
 *  @param screens screen data.
 *  @return void.
 */
void destroy_screens(Screens *screens);

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

/*  @brief Draw find book screen.
 *
 *  Draw find book screen.
 *
 *  @param data program's all data.
 *  @return void.
 */
void draw_find_book_screen(Data const *data);
/*  @brief Process menu admin screen's input data.
 *
 *  Process menu admin screen's input data.
 *
 *  @param input Input string.
 *  @param data Program's all data.
 *  @return void.
 */
void input_find_book_screen(const wchar_t const *input, Data const *data);

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

    setlocale(LC_ALL , "");

    data.clients = init_clients(STRING_CLIENT_FILE);
    data.books = init_books(STRING_BOOK_FILE);
    data.borrows = init_borrows(STRING_BORROW_FILE);

    data.screens = init_screens();

    data.is_running = 1;
    while (data.is_running)
    {
        clear_screen();
        draw_screen(data.screens, &data);
        input_screen(data.screens, &data);
    }

    destroy_clients(data.clients, STRING_CLIENT_FILE);
    destroy_books(data.books, STRING_BOOK_FILE);
    destroy_borrows(data.borrows, STRING_BORROW_FILE);

    destroy_screens(data.screens);

    return 0;
}

LinkedList *init_clients(const char const *file_name) { }
LinkedList *init_books(const char const *file_name) { }
LinkedList *init_borrows(const char const *file_name) { }

Book *create_book(const LinkedList const *book_list, const wchar_t const *name, const wchar_t const *publisher, const wchar_t const *author, const wchar_t const *ISBN, const wchar_t const *location)
{
    Book *book_p = malloc(sizeof(Book));
    int len;
    
    len = wcslen(name);
	book_p->name = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(book_p->name, name)
    len = wcslen(publisher);
	book_p->publisher = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(book_p->publisher, publisher)
    len = wcslen(author);
	book_p->author = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(book_p->author, author)
    len = wcslen(location);
	book_p->location = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(book_p->location, location)
    wcscpy(book_p->ISBN, ISBN);
	book_p->availability = L'Y';

	LinkedList *current = book_list->next;//여기서부터는 가장 최근의(큰) 도서번호를 구하는 과정임
	LinkedList *largest = current;

	while (current != NULL)	{
		if (wcscmp(((Book *)current->contents)->number, ((Book *)largest->contents)->number) > 0)
			largest = current;
		current = current->next;
	}

	int largest_num;
	swscanf((Book *)largest->contents)->number, L"%d", &largest_num);
	swprintf(book_p->number, SIZE_BOOK_NUMBER + 1, L"%07d", largest_num + 1);

	return book_p;
}
Borrow *create_borrow(Client const *client, Book const *book)
{
    Borrow * borrow_p = (Borrow *)malloc(sizeof(Borrow));
    borrow_p->loan_date = time(NULL);
	struct tm *t;
	t = localtime(&borrow_p->loan_date);

	wcscpy(borrow_p->student_number, client->student_number);
	wcscpy(borrow_p->book_number, book->number);
	
	if ((t->tm_wday + 30) / 7 == 0) //(t->tm_wday+30)/7==30일 뒤의 요일
		borrow_p->return_date = borrow_p->loan_date + 31 * 24 * 60 * 60;
	else
		borrow_p->return_date = borrow_p->loan_date + 30 * 24 * 60 * 60;

	return borrow_p;
}

void print_client(const Client const *client) { }
void print_book(const Book const *book)
{
    wprintf(
        L"도서명 : %ls \n"
	    L"출판사 : %ls \n"
	    L"저자명 : %ls \n"
	    L"ISBN : %ls \n"
	    L"소장처 : %ls \n"
	    L"대여가능 여부 : %lc \n",
        book->name, book->publisher, book->author, book->ISBN, book->location book->availability);
	return;
}
void print_borrow(const Borrow const *borrow)
{
    struct tm * loan_, *return_;
	loan_ = localtime(&(borrow->loan_date));
	return_ = localtime(&(borrow->return_date));
	wprintf(
        L"도서번호 : %s \n"
	    L"도서명 : %s \n"
	    L"대여일자 : %d년 %d월 %d일 ",
        borrow->book_number, borrow->book_name, loan_->tm_year + 1900, loan_->tm_mon + 1, loan_->tm_mday);
	switch (loan_->tm_wday)
    {
	case 0:
		wprintf(L"일요일\n");
		break;
	case 1:
		wprintf(L"월요일\n");
		break;
	case 2:
		wprintf(L"화요일\n");
		break;
	case 3:
		wprintf(L"수요일\n");
		break;
	case 4:
		wprintf(L"목요일\n");
		break;
	case 5:
		wprintf(L"금요일\n");
		break;
	case 6:
		wprintf(L"토요일\n");
		break;
	default:
		break;
	}
	wprintf(L"반납일자 : %d년 %d월 %d일 ", return_->tm_year + 1900, return_->tm_mon + 1, return_->tm_mday);
	switch (loan_->tm_wday)
    {
	case 0:
		wprintf(L"일요일\n");
		break;
	case 1:
		wprintf(L"월요일\n");
		break;
	case 2:
		wprintf(L"화요일\n");
		break;
	case 3:
		wprintf(L"수요일\n");
		break;
	case 4:
		wprintf(L"목요일\n");
		break;
	case 5:
		wprintf(L"금요일\n");
		break;
	case 6:
		wprintf(L"토요일\n");
		break;
	default:
		break;
	}

	return;
}

void print_clients(const LinkedList const *client_list) { }
void print_books(const LinkedList const *book_list) { }
void print_borrows(const LinkedList const *borrow_list) { }

void save_clients(const LinkedList const *client_list, const char const *file_name) { }
void save_books(const LinkedList const *book_list, const char const *file_name) { }
void save_borrows(const LinkedList const *borrow_list, const char const *file_name) { }

LinkedList *insert_client(LinkedList const *client_list, const Client const *client) { }
LinkedList *insert_book(LinkedList const *book_list, const Book const *book) { }
LinkedList *insert_borrow(LinkedList const *borrow_list, const Borrow const *borrow) { }

Client *find_client_by_student_number(const LinkedList const *client_list, const wchar_t const *student_number) { }
LinkedList *find_books_by_name(const LinkedList const *book_list, const wchar_t const *book_name) { }
LinkedList *find_books_by_ISBN(const LinkedList const *book_list, const wchar_t const *book_ISBN) { }
LinkedList *find_books_by_author(const LinkedList const *book_list, const wchar_t const *book_author) { }
LinkedList *find_books_by_publisher(const LinkedList const *book_list, const wchar_t const *book_publisher) { }
Book *find_book_by_number(const LinkedList const *book_list, const wchar_t const *book_number) { }
LinkedList *find_borrows_by_client(Client const *client) { }
Borrow *find_borrow(Client const *client, Book const *book) { }

void remove_client(LinkedList const *client_list, Client const *client) { }
void remove_book(LinkedList const *book_list, Book const *book) { }
void remove_borrow(LinkedList const *borrow_list, Borrow const *borrow) { }

void destroy_list(LinkedList *list) { }

void destroy_clients(LinkedList *client_list, const char const *file_name) { }
void destroy_books(LinkedList *book_list, const char const *file_name) { }
void destroy_borrows(LinkedList *borrow_list, const char const *file_name) { }

void destroy_client(Client const *client) { }
void destroy_book(Book const *book) { }
void destroy_borrow(Borrow const *borrow) { }

Screens *init_screens(void)
{
    Screens *screens = malloc(sizeof(Screens));
    screens->type = SCREEN_INIT;

    screens->screens[SCREEN_INIT].type = SCREEN_INIT;
    screens->screens[SCREEN_INIT].draw = draw_init_screen;
    screens->screens[SCREEN_INIT].input = input_init_screen;

    screens->screens[SCREEN_MENU_ADMIN].type = SCREEN_MENU_ADMIN;
    screens->screens[SCREEN_MENU_ADMIN].draw = draw_menu_admin_screen;
    screens->screens[SCREEN_MENU_ADMIN].input = input_menu_admin_screen;

    screens->screens[SCREEN_MENU_MEMBER].type = SCREEN_MENU_MEMBER;
    screens->screens[SCREEN_MENU_MEMBER].draw = draw_menu_member_screen;
    screens->screens[SCREEN_MENU_MEMBER].input = input_menu_member_screen;
    
    screens->screens[SCREEN_SIGN_IN].type = SCREEN_SIGN_IN;
    screens->screens[SCREEN_SIGN_IN].draw = draw_sign_in_screen;
    screens->screens[SCREEN_SIGN_IN].input = input_sign_in_screen;
    
    screens->screens[SCREEN_SIGN_UP].type = SCREEN_SIGN_UP;
    screens->screens[SCREEN_SIGN_UP].draw = draw_sign_up_screen;
    screens->screens[SCREEN_SIGN_UP].input = input_sign_up_screen;

    screens->screens[SCREEN_FIND_BOOK].type = SCREEN_FIND_BOOK;
    screens->screens[SCREEN_FIND_BOOK].draw = draw_find_book_screen;
    screens->screens[SCREEN_FIND_BOOK].input = input_find_book_screen;

    return screens;
}
void change_screen(Screens const *screens, char type)
{
    screens->pre_screen_type = screens->type;
    screens->type = type;
}
void clear_screen(void)
{
    printf("\x1B[2J\x1B[1;1H");
}
void draw_screen(Screens const *screens, Data const *data)
{
    screens->screens[screens->type].draw(data)
}
void input_screen(Screens *screens, Data const *data)
{
    wchar_t input[SIZE_INPUT_MAX] = { 0 };
    wscanf(L"%ls", input);

    screens->screens[screens->type].input(input, data);
}
void destroy_screens(Screens *screens)
{
    if (screens != NULL)
        free(screens);
}

void draw_init_screen(Data const *data) 
{
    wprintf(
        L">> 도서관 서비스 <<\n"
        L"1. 회원 가입           2. 로그인           3. 프로그램 종료\n"
        L"번호를 선택하세요: ");
}
void input_init_screen(const wchar_t const *input, Data const *data)
{
    if (input == NULL || data == NULL)
        return;
    if (data->is_admin)
        data->is_admin = 0;
    data->login_client = NULL;

    switch (input[0])
    {
    case L'1':
        change_screen(data->screens, SCREEN_SIGN_UP);
        break;
    case L'2':
        change_screen(data->screens, SCREEN_SIGN_IN);
        break;
    case L'3':
        data->is_running = 0;
        break;
    default:
        break;
    }
}

void draw_sign_up_screen(Data const *data)
{
    wprintf(
        L">> 회원 가입 <<\n"
        L"학번, 비밀번호, 이름, 주소, 전화번호를 입력하세요.\n"
        L"\n"
        L"학번: ");
}
void input_sign_up_screen(const wchar_t const *input, Data const *data)
{
    if (input == NULL || data == NULL)
        return;
    wchar_t input_tmp[SIZE_INPUT_MAX] = { 0 };
    wchar_t *input_p = NULL;
    size_t len = 0;

    Client *client = malloc(sizeof(Client));

    len = wcslen(input);
    input_p = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(input_p, input);
    client->student_number = input_p;

    wprintf(L"비밀번호: ");
    wscanf(L"%ls", input_tmp);
    len = wcslen(input_tmp);
    input_p = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(input_p, input_tmp);
    client->password = input_p;

    wprintf(L"이름: ");
    wscanf(L"%ls", input_tmp);
    len = wcslen(input_tmp);
    input_p = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(input_p, input_tmp);
    client->name = input_p;

    wprintf(L"주소: ");
    wscanf(L"%ls", input_tmp);
    len = wcslen(input_tmp);
    input_p = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(input_p, input_tmp);
    client->address = input_p;

    wprintf(L"전화번호: ");
    wscanf(L"%ls", input_tmp);
    len = wcslen(input_tmp);
    input_p = malloc(sizeof(wchar_t) * (len + 1));
    wcscpy(input_p, input_tmp);
    client->phone_number = input_p;

    insert_client(data->clients, client);
    save_clients(data->clients, STRING_CLIENT_FILE);
    wprintf(L"회원가입이 되셨습니다.");
    sleep(1);
    change_screen(data->screens, SCREEN_INIT);
}

void draw_sign_in_screen(Data const *data)
{
    wprintf(
        L">> 로그인 <<\n"
        L"학번: ");
}
void input_sign_in_screen(const wchar_t const *input, Data const *data)
{
    if (input == NULL || data == NULL)
        return;
    wchar_t input_tmp[SIZE_INPUT_MAX] = { 0 };

    Client *client = find_client_by_student_number(data->clients, input);

    if (wcscmp("admin", input) == 0)
    {
        if (client == NULL)
        {
            client = malloc(sizeof(Client));

            len = wcslen(input);
            wchar_t *input_p = malloc(sizeof(wchar_t) * (len + 1));
            wcscpy(input_p, input);
            client->student_number = input_p;

            insert_client(data->clients, client);
            save_clients(data->clients, STRING_CLIENT_FILE);
        }

        data->is_admin = 1;
        data->login_client = client;
        return; 
    } 
    if (client == NULL && !data->is_admin)
    {
        wprintf(L"회원정보가 없습니다.");
        sleep(1);
        change_screen(data->screens, SCREEN_INIT);

        return;
    }

    wprintf(L"비밀번호: ");
    wscanf(L"%ls", input_tmp);

    if (data->is_admin)
    {
        wprintf(L"로그인이 되셨습니다.");
        sleep(1);
        change_screen(data->screens, SCREEN_MENU_ADMIN);
        return;
    }
    if (wcscmp(client->password, input_tmp) == 0)
    {
        data->login_client = client;
        wprintf(L"로그인이 되셨습니다.");
        sleep(1);
        change_screen(data->screens, SCREEN_MENU_MEMBER);
    }
    else
    {
        wprintf(L"잘못된 비밀번호입니다.");
        sleep(1);
        change_screen(data->screens, SCREEN_INIT);
    }
}

void draw_menu_member_screen(Data const *data)
{
    wprintf(
        L">> 회원 메뉴 <<\n"
        L"1. 도서 검색           2. 내 대여 목록\n"
        L"3. 개인정보 수정       4. 회원 탈퇴\n"
        L"5. 로그아웃            6. 프로그램 종료\n"
        L"\n"
        L"번호를 선택하세요: ");
}
void input_menu_member_screen(const wchar_t const *input, Data const *data)
{
    if (input == NULL || data == NULL)
        return;

    switch (input[0])
    {
    case L'1':
        change_screen(data->screens, SCREEN_FIND_BOOK);
        return;
    case L'2':
        wprintf(L">> 내 대여 목록 <<\n");
        print_borrows(find_borrows_by_client(data->clients));
        sleep(3);
        return;
    case L'6':
        data->is_running = 0;
        return;
    default:
        return;
    }
}

void draw_menu_admin_screen(Data const *data)
{
    wprintf(
        L">> 관리자 메뉴 <<\n"
        L"1. 도서 등록           2. 도서 삭제\n"
        L"3. 도서 대여           4. 도서 반납\n"
        L"5. 도서 검색           6. 회원 목록\n"
        L"7. 로그아웃            8. 프로그램 종료\n"
        L"\n"
        L"번호를 선택하세요: ");
}
void input_menu_admin_screen(const wchar_t const *input, Data const *data)
{
    if (input == NULL || data == NULL)
        return;

    switch (input[0])
    {
    case L'5':
        change_screen(data->screens, SCREEN_FIND_BOOK);
        return;
    case L'8':
        data->is_running = 0;
        break;
    default:
        break;
    }
}

void draw_find_book_screen(Data const *data)
{
    wprintf(
        L">> 도서 검색 <<\n"
        L"1. 도서명 검색           2. 출판사 검색\n"
        L"3. ISBN 검색            4. 저자명 검색\n"
        L"5. 전체 검색             6. 이전 메뉴\n"
        L"\n"
        L"번호를 선택하세요: ");
}
void input_find_book_screen(const wchar_t const *input, Data const *data)
{
    if (input == NULL || data == NULL)
        return;

    wchar_t find_data[SIZE_INPUT_MAX] = { 0 };
    LinkedList *current_books = NULL;

    switch (input[0])
    {
    case L'1':
        wprintf(L"도서명을 입력하세요: ");
        wscanf("%ls", find_data);
        current_books = find_books_by_name(data->books, find_data);
        break;
    case L'2':
        wprintf(L"출판사를 입력하세요: ");
        wscanf("%ls", find_data);
        current_books = find_books_by_publisher(data->books, find_data);
        break;
    case L'3':
        wprintf(L"ISBN을 입력하세요: ");
        wscanf("%ls", find_data);
        current_books = find_books_by_ISBN(data->books, find_data);
        break;
    case L'4':
        wprintf(L"저자명을 입력하세요: ");
        wscanf("%ls", find_data);
        current_books = find_books_by_author(data->books, find_data);
        break;
    case L'5':
        current_books = data->books;
        break;
    case L'6':
        change_screen(data->screens, data->screens->pre_screen_type);
        return;
    default:
        return;
    }
    wprintf(L">> 검색 결과 <<\n");
    print_books(current_books);
    sleep(3);
}
