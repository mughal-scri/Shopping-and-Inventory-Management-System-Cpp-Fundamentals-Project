// *********************************************************************************************************************
// ************                                 HEADERS FILES                                       ********************
// *********************************************************************************************************************
#include <iostream> // Input/Output Operations
#include <iomanip>  // Output Formatting
#include <string>   // String Manipulation
#include <fstream>  // File Operations
#include <sstream>  // String Stream Operations
#include <vector>   // Dynamic Array Container
#include <cstdlib>  // System Commands
#include <cctype>   // Character Handling
#include <limits>   // Numeric Limits
#include <ctime>    // Time Functions for Discounts
using namespace std;
// ********************************************************************************************************************
// *********************                      FUNCTION PROTOTYPES                         *****************************
// ********************************************************************************************************************
//                             ADMIN FUNCTION PROTOTYPES
int admin();
bool admin_login();
struct Category_Information
{
    string file_path;
    string Short_Code;
    string category_name;
};
struct products
{
    string ID;
    string name;
    double price;
    int stock;
};
int Add_product();
bool low_stock_check();
int Remove_products();
int Update_products();
int View_sales_report();
int show_products_lists();
int add_discount_coupon();
void Admin_privileges();
void Re_show_products(string const &filename);

//                             CUSTOMER FUNCTION PROTOTYPES
int customer();
struct Customer
{
    vector<string> Name;
    vector<string> Password;
    vector<string> Authentication;
};
Customer Cus;
bool customer_login();
int make_new_account();
struct Cart
{
    const int cart_UL = 50; // the maximum amount of the items  cart can hold
    vector<string> ID;
    vector<string> Name;
    vector<double> price;
    vector<unsigned int> Quantity;
    vector<double> Total_price;
};
Cart CustomerCart;
Cart Add_to_Cart(string const &file_to_open);
int shopping_interface();
void customer_previleges();
void show_cart();
void bill_generation();
void settings();
void updating_stock_after_Purchase();
string customername;
double currencymode;
string CurrencyType;
void remove_from_cart();
void show_cart_items();

//                       UNIVERSAL USE OF FUNCTIONS   a.k.a  Miscellaneous functions
Category_Information category_selection();
void category_showing();
products updation(const products &product);
void currencytype();
double currency(double price);
int discounts(double sum_price);
void discount_Reveal_criteria(double const &grand_sum);
double grand_price, disc_given;
void customer_data();
void re_show_discounts(string const &filename);

/***************************************************************************************************************************************************
 *****************************                       MAIN FUNTION                                  *************************************************
 ***************************************************************************************************************************************************/
main()
{
    char Login_method;
    int returned;
    while (true)
    {
        system("cls");
        cout << "------------------------------------------------------------------------------------------------" << endl
             << "--------------------------------- MUGHAL ONLINE MART -------------------------------------------" << endl
             << "------------------------------------------------------------------------------------------------\n"
             << endl;
        cout << "Choose your Login Method" << endl
             << "\nMethod     \t  Keyword " << endl
             << "\nADMIN LOGIN\t A" << endl
             << "\nCUSTOMER LOGIN\t C\n"
             << endl
             << "\nTo Exit       \t E\n"
             << endl
             << "\nEnter your choice: ";
        cin >> Login_method;
        cin.ignore();
        if (Login_method == 'A' || Login_method == 'a')
        {
            admin();
        }
        else if (Login_method == 'C' || Login_method == 'c')
        {
            customer();
        }
        else if (Login_method == 'E' || Login_method == 'e')
            break;
        else
            cout << "\nInvalid Value Entered";
    }
    return 0;
}

/***************************************************************************************************************************************************
 *****************************                 ADMIN FUNTION & it's Related Previleges             *************************************************
 ***************************************************************************************************************************************************/
//                       ADMIN LOGIN Details and MAIN Admin function
int admin()
{
    bool Proceed_or_not;
    char other_task;
    //                  First The Control will be taken towards the login interface
    system("cls");
    cout << "---------------------------------- Welcome To Admin Login Inteface ---------------------------------------" << endl
         << "\n You have to Login First if you want to use the Administrator Previleges \n"
         << endl;
    Proceed_or_not = admin_login();
    // If the Login Bypass returns True means Admin Credentials  are correct
    if (Proceed_or_not == true)
    {
        // first of all the self run chk of products low stock But Admin has the previlege to chk again too but here it is self run after login is successful
        system("pause");
        system("cls");
        low_stock_check();
        cout << endl
             << "\nGoing onto the Previleges Window!" << endl;
        system("pause");
    Reloop_back:
        // now admin will be redirected towards the Previleges Window
        system("cls");
        char Admin_choice;
        cout << "------------------------------------ Admin Previleges Interface -------------------------------------" << endl
             << "\nChoose what you want to do as an Administrator \n"
             << endl;
        // His Previges List will be shown to them and He'll be asked to make a selection
        Admin_privileges();
    task_entry: // goto Control if user inputs the wrong keyword from the selection shown
        cout << endl
             << "\nEnter your choice: ";
        cin >> Admin_choice;
        cin.ignore();
        //              According the the Admin's selection the following control will run
        switch (Admin_choice)
        {
        case 'A':
        case 'a':
            Add_product();
            break;
        case 'R':
        case 'r':
            Remove_products();
            break;
        case 'U':
        case 'u':
            Update_products();
            break;
        case 'V':
        case 'v':
            View_sales_report();
            break;
        case 'S':
        case 's':
            show_products_lists();
            break;
        case 'd':
        case 'D':
            add_discount_coupon();
            break;
        case 'L':
        case 'l':
            low_stock_check();
            break;
        case 'E':
        case 'e':
            return 0;
        default:
        {
            cout << "\nInvalid Value Entered";
            goto task_entry;
        }
        }
        goto Reloop_back;
    }
    /*
    this control will only run if the User Fails to enter correct credentials of the Admin
        and he'll be redirected back to the main panel of admin/customer selection
    */
    else
    {
        cout << "\nFailed to log in to the admin panel. Returning to main menu." << endl;
        system("pause");
        return 1;
    }
}
//                      To show the previleges Menu to the Admin,
void Admin_privileges()
{
    cout << endl
         << "\nPrevileges    \t\t  Keyword " << endl
         << "\nAdd Products    \t\t   A" << endl
         << "\nRemove Products \t\t   R" << endl
         << "\nUpdate Products \t\t   U" << endl
         << "\nShow Products   \t\t   S" << endl
         << "\nView Sales Report  \t\t   V" << endl
         << "\nAdd New Discount Coupon   \t   D" << endl
         << "\nCheck Low Stock \t\t   L" << endl
         << "\nExit Admin Window\t\t   E";
}

bool admin_login()
{
    // A struct container that will store the information of the admin credentials entered by the user
    struct Admin
    {
        string Name;
        string Password;
        string Authentication;
    };
    Admin Ad;
    // Related file that contains the admin's credentials and opening it in read only mode
    ifstream reading("D:\\coding\\C++_Project\\Project Related FIles\\Logins\\Admin Login.txt");
    if (!reading)
    {
        cout << "Unable to Open file";
        return 1;
    }
    else
    {
        string line[3];
        int i = 0, count = 5;
        // this will read the file and store it in the array of string named line
        while (i < 3 && getline(reading, line[i]))
        {
            i++;
        }
        reading.close();
        //  After reading the credential chk loop controlled flow will run using the do-while statement
        do
        {
            /*if will only run if the credentials entered by the user are incorrect
            and these if will help in avoiding re-entering them all if only one of them is incorrect --- To Save User's time */
            if (Ad.Name != line[0])
            {
                cout << "\nEnter Admin name: ";
                getline(cin, Ad.Name);
            }
            if (Ad.Password != line[1])
            {
                cout << "\nEnter Admin Password: ";
                getline(cin, Ad.Password);
            }
            if (Ad.Authentication != line[2])
            {
                cout << "\nEnter Two Step authentication: ";
                getline(cin, Ad.Authentication);
            }
            // This if-else statement will chk and compare the credential details entered by the user
            //  if the information is correct return True
            if (Ad.Name == line[0] && Ad.Password == line[1] && Ad.Authentication == line[2])
            {
                cout << "\nLogin Successful\nYou are now allowed to use the previliges of the Administrator" << endl;
                break;
                return true;
            }
            // if credentials are incorrect reduce the counter by 1
            else
            {
                cout << "\nIncorrect Login Credentials!\n";
                count--;
                cout << "You have only " << count << " left to guess!\n";
            }
        } while (count > 0); // iterate while the count is not zero if becomes zero terminate loop
        // as the loop terminates count automatically becomes zero so function will auto returns false
        if (count == 0)
            return false;
    }
}

//                          ADD Product with Auto-Generated Product ID different for each category!
int Add_product()
{
    // a struct container that'll hold the Product information user entered
    struct Add_Products
    {
        string Name;
        float Price;
        int stock;
        string ID;
    };
    char another_product, other_category;
    // loop to add another product in any other category
    do
    {
        system("cls");
        cout << "-------------------------------------------- ADD PRODUCTS WINDOW ----------------------------------------------------" << endl;
        // selection will store the related file information admin wants to open
        Category_Information selection = category_selection();
        string file_to_open = selection.file_path; // file's path
        string short_code = selection.Short_Code;  // file's short code to auto-generate it's ID
        string line;
        int count = 1;
        //                                           Reading file to decide Product ID Afterwards
        ifstream reading(file_to_open.c_str());
        if (!reading)
        {
            cout << "Unable to Open file";
            return 1;
        }
        else
        {
            //          This will Show the existing products in the category file Admin Selected
            Re_show_products(file_to_open);
            while (getline(reading, line))
            {
                count++;
            }
        }
        reading.close();
        //      Do-While Loop to add multiple products
        do
        {
            //                  Opening file in append mode to add products
            ofstream writing(file_to_open.c_str(), ios::app);
            if (!writing)
            {
                cout << "Unable to Open file";
                return 1;
            }
            else
            {
                // Instance of the container and asking for products details - name, Price, Stock he wants to add
                Re_show_products(file_to_open);
                Add_Products AP;
                cin.ignore();
                cout << "Enter Product Name: ";
                getline(cin, AP.Name);
                cout << "Enter Product Price: ";
                cin >> AP.Price;
                cout << "Enter Product Stock: ";
                cin >> AP.stock;
                AP.ID = short_code + "-" + to_string(count); //    this single line will generate the ID automatically and
                cout << "\nThe Auto-Generated Product ID for this product is: " << AP.ID << endl;

                //                  Replacing spaces with '-' in Product Name for better file handling in later Uses
                for (char &name : AP.Name)
                {
                    if (name == ' ')
                        name = '-';
                }

                writing << left << setw(12) << AP.ID << setw(35) << AP.Name << setw(10) << AP.Price << setw(8) << AP.stock << endl;
                count++;         // here the counter will be increased by one to avoid generating the same ID as generated for previously added product
                writing.close(); // closing the file a so each time the file is opened pointer auto sets to end of file
                Re_show_products(file_to_open);
                cout << "\nProduct Added to Successfully!\n"
                     << endl;
            }
            // asking if he wants to add any other product in this category
            cout << "\nDo you want to add another product? (Y/N): ";
            cin >> another_product;
        } while (another_product != 'N' && another_product != 'n');
        // asking if he wants to add product to any other category
        cout << "Want to add Products to any other category(Y/N): ";
        cin >> other_category;
    } while (other_category != 'N' && other_category != 'n');
}

//                                         Remove Product using its Product ID
int Remove_products()
{
    //    Some Vairables Declared
    string PD_ID_to_rem, file_to_open, temp_file, line, ID, name;
    int price, stock;
    char another_product, Other_category;
    //----------------------------------- Outer do-while loop for the functioning of Categories ---------------------------------------
    do
    {
        //  Clear the screen after each iteration
        system("cls");
        cout << "-------------------------------------- REMOVE PRODUCTS WINDOW -------------------------------------------" << endl;
        Category_Information selection = category_selection();
        file_to_open = selection.file_path;
        temp_file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\temp.txt";
        // Opening Existing file and making a temporary file in the same directory
        ifstream readingfile(file_to_open.c_str());
        ofstream writingfile(temp_file.c_str());
        // Checking if both the files are open or not
        if (!readingfile || !writingfile)
        {
            cout << "Either Files can't be opened or not found!" << endl;
            return 1;
        }
        else
        {
            // ------------------------------------------------- Inner Loop for functioning of products-----------------------------------------------------
            do
            { // First of all, reading the existing products information in the category
                string sline;
                int count = 1;
                Re_show_products(file_to_open);
                //  Clearing and repositioning the pointer to the beginning of the file
                readingfile.clear();
                readingfile.seekg(0, ios::beg);
                // Asking what product he wants to remove from the list by writing its ID
                cout << "\nEnter the Product by ID: ";
                cin >> PD_ID_to_rem;
                for (char &I : PD_ID_to_rem)
                    I = toupper(I);
                // Again reading the entire file and removing if the product is present in the list of file
                while (getline(readingfile, line))
                {
                    stringstream RF_ID(line); // stringstream divides the whole string into smaller chunks
                    RF_ID >> ID >> name >> price >> stock;
                    if (ID != PD_ID_to_rem)
                    { // checking whether the ID matches the users concern if not writing it into the file
                        ID = selection.Short_Code + "-" + to_string(count);
                        writingfile << left << setw(12) << ID << setw(35) << name << setw(10) << price << setw(8) << stock << endl; // this will rewrite the whole data into temp file with a newly assigned ID
                        count++;                                                                                                    // counter is working to assign a new ID starting from 1 each time user removes a product from the file
                    }
                }
                //      closing the both files temporary made and the previous one
                readingfile.close();
                writingfile.close();
                //      Removing the previous file and renaming the temporary file with the previous ones name
                remove(file_to_open.c_str());
                rename(temp_file.c_str(), file_to_open.c_str());
                Re_show_products(file_to_open);
                cout << "\nProduct Removed Successfully!\n"
                     << endl;
                //     Asking if the user wants to remove any other product from the category
                cout << "Do you want to remove any other product(Y/N): ";
                cin >> another_product;
            } while (another_product != 'N' && another_product != 'n');
            //      Asking if the user wants to remove any product from any other Category
            cout << "Do you want to remove Products from any other category(Y/N): ";
            cin >> Other_category;
        }
    } while (Other_category != 'N' && Other_category != 'n');
}

//             Updating prices name and other things related to products except the ID as ID cannot be changed
int Update_products()
{
    //    Some Vairables Declared
    string PD_ID_to_rem, file_to_open, temp_file, line, ID, name;
    int stock;
    double price;
    char another_product, Other_category;
    //----------------------------------- Outer do-while loop for the functioning of Categories ---------------------------------------
    do
    {
        //  Clear the screen after each iteration
        system("cls");
        cout << "-------------------------------------- UPDATE PRODUCTS WINDOW -------------------------------------------" << endl;
        Category_Information selection = category_selection();
        file_to_open = selection.file_path;
        temp_file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\temp.txt";
        // ------------------------------------------------- Inner Loop for functioning of products-----------------------------------------------------
        do
        {
            // Opening Existing file and making a temporary file in the same directory
            ofstream writingfile(temp_file.c_str());
            ifstream readingfile(file_to_open.c_str());
            // Checking if both the files are open or not
            if (!readingfile)
            {
                cout << "File can't be opened or not found!" << endl;
                return 1;
            }
            else
            {
                // First of all, reading the existing products information in the category
                string sline;
                Re_show_products(file_to_open);

                // Asking what product he wants to Update from the list by writing its ID
                cout << "\nNow, Enter the Product by ID, that you want to edit\nNote: the ID of Product cannot be changed\nEnter ID:  ";
                cin >> PD_ID_to_rem;
                for (char &ID : PD_ID_to_rem)
                    ID = toupper(ID);
                while (getline(readingfile, line))
                {
                    stringstream RF_ID(line); // stringstream divides the whole string into smaller chunks
                    RF_ID >> ID >> name >> price >> stock;
                    if (ID == PD_ID_to_rem)
                    { // checking whether the ID matches the users concern if not writing it into the file
                        products Old_Product = {ID, name, price, stock};
                        products Upd_product = updation(Old_Product);
                        writingfile << left << setw(12) << Upd_product.ID << setw(35) << Upd_product.name << setw(10) << Upd_product.price << setw(8) << Upd_product.stock << endl;
                    }
                    else
                    {
                        writingfile << left << setw(12) << ID << setw(35) << name << setw(10) << price << setw(8) << stock << endl;
                    }
                }

                //      closing the files
                readingfile.close();
                writingfile.close();

                //      Removing the previous file and renaming the temporary file with the previous ones name
                remove(file_to_open.c_str());
                rename(temp_file.c_str(), file_to_open.c_str());
                Re_show_products(file_to_open);
                cout << "\nProduct Updated Successfully!\n"
                     << endl;
                //     Asking if the user wants to Update any other product from the category
                cout << "\nDo you want to update any other product(Y/N): ";
                cin >> another_product;
            }

            //      Asking if the user wants to update any product from any other Category
        } while (another_product != 'N' && another_product != 'n');
        cout << "\nDo you want to Update Products from any other category Menu Mentioned Above(Y/N): ";
        cin >> Other_category;
    } while (Other_category != 'N' && Other_category != 'n');
    system("cls");
}

//                     Showing the Sales Report to the Admin, IDK how?????
int View_sales_report()
{
    system("cls");
    cout << "--------------------------------------------- Sales Report Window -----------------------------------------------------\n"
         << endl;
    // Opening Related file from the directory in read-only mode
    ifstream readfile("D:\\coding\\C++_Project\\Project Related FIles\\Sales Reports\\Sales.txt");
    if (!readfile)
    {
        cout << "\nError Opening the file!";
        return 1;
    }
    else
    {
        // Here the DATA Contained in the file will be read line by line and will be shown to the admin
        cout << "Reading the Data of Sales Report. Please wait!\n";
        system("pause");
        string line;
        while (getline(readfile, line))
        {
            cout << line << endl;
        }
        cout << endl
             << "\n---------------------------------------------" << endl
             << "     END OF SALES REPORT" << endl
             << "---------------------------------------------\n";
        system("pause");
        return 0;
    }
}

//                      Introduce exclusive Discount/Promo codes or Coupon setting
int add_discount_coupon()
{
    // Opening Related file first in read-mode and then again in write-mode
    system("cls");
    string filename = "D:\\coding\\C++_Project\\Project Related FIles\\Discount Codes\\Discount & promo Codes.txt";
    char another_code;
    ofstream write;
    cout << "------------------- Introduce New promo/Discout Coupon Window -----------------------------------" << endl;
    if (!write)
    {
        cout << "\nFile not found or cannot be opened!\n";
        return 1;
    }
    else
    {
        do
        {
            // this will read the file and show the existing codes on the screen
            re_show_discounts(filename);
            write.open(filename.c_str(), ios::app);
            // closing the read-mode and starting the write mode
            cout << "\nEnter A new Discount or promo code (Ex. IFellForIt, avoid spaces): ";
            string code;
            cin >> code;
            cout << "\nHow much Discount or promo it'll offer to a customer(can be 2.5, 7.5 etc): ";
            double offers;
            cin >> offers;
            cout << "\nHow much customers can avail it on basis of Come First, Served First(like 10 / 20 / 50): ";
            int avail;
            cin >> avail;
            write << left << setw(35) << code << setw(20) << offers << setw(20) << avail << endl; // this line will write the code in the file
            write.close();                                                                        // closing the write mode file too
            re_show_discounts(filename);
            cout << "\nNew Code is now added to the Discount file!\n";
            cout << endl
                 << "Do you want to add another promo/discount coupon to the list (Y/N): ";
            cin >> another_code;
        } while (another_code != 'N' && another_code != 'n');
    }
}

//                      Self Running module that'll check and give output to the Admin - No Admin's Interaction required to RUN
bool low_stock_check()
{
    system("cls");
    // Related Array of strings that contains file information that Will be opened
    string Categoryfilespath[] = {"D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Computer and Electronics.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Beverages.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Kitchen Accessories.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\DIY and Hardware.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Sports and Outdoors.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Bedroom Equipment.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Stationery and Books.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Bathroom Equipment.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Beauty and Personal Care.txt",
                                  "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Perfumes and Fragrances.txt"};
    string category[] = {"Computer and Electronics", "Beverages", "Kitchen Accessories", "DIY and Hardware", "Sports and Outdoors",
                         "Bedroom Equipment", "Stationery and Books", "Bathroom Equipment", "Beauty and Personal Care", "Perfumes and Fragrances"};
    cout << endl
         << "----------------------- LOW STOCK REPORT -----------------------" << endl;
    cout << left << setw(12) << "\nID" << setw(35) << "NAME" << setw(10) << "Price" << setw(8) << "Stock" << endl;
    /*
                                    TWO BOOL VARIABLES DECLARED FOR DIFFERENT FUNCTIONALITY
    found_low_stock ---> will become true only if any one product from any category has low stock and will remain true through out
    fls_category ---> will become true if the category that is being read has any low stock present    */
    bool found_low_stock = false;
    bool fls_category = false;
    // Loop Iteration to read each file one by one whose directory is stored in array of string
    for (int i = 0; i < 10; i++)
    {
        // fls_confirmed will become false for iteration to avoid printing false control
        bool fls_category = false;
        // false_confirmed will also be overwritten to zero works will the fls_category
        int false_confirmed = 0;
        // Opening file in Read-Only mode
        ifstream checking_for_low_stock(Categoryfilespath[i].c_str());
        if (!checking_for_low_stock)
        {
            cout << "Error Opening file: " << category[i] << endl;
            continue;
        }
        else
        {
            string line, name, ID;
            double Price;
            int stock;
            // this will read file line by line
            while (getline(checking_for_low_stock, line))
            {
                stringstream Breaking_string(line); // parsing the string line to seperate info of stock
                Breaking_string >> ID >> name >> Price >> stock;
                // first priority given to zero stock
                if (stock == 0)
                {
                    // both will become true if but one will remain permanent throughout
                    found_low_stock = true;
                    fls_category = true;
                    false_confirmed++;        // this counter seems useless but is very useful for below if statement
                    if (false_confirmed == 1) // Reason for the one that has to become true in each iteration so only related file info will be shown
                    {
                        cout << endl
                             << "\nFrom Category: " << category[i] << endl;
                    }
                    cout << left << setw(12) << ID << setw(35) << name << setw(10) << Price << setw(8) << stock << setw(20) << "No Stock left, Restock them!" << endl;
                }
                else if (stock <= 5 && stock > 0)
                {
                    // both will become true if but one will remain permanent throughout
                    found_low_stock = true;
                    fls_category = true;
                    false_confirmed++;
                    if (false_confirmed == 1) // this will only run if the counter is 1 to avoid reprinting eachtime low-stock product is found
                    {
                        cout << "\nFrom Category: " << category[i] << endl;
                    }
                    cout << left << setw(12) << ID << setw(35) << name << setw(10) << Price << setw(8) << stock << setw(20) << "Very few Stock left!" << endl;
                }
                else
                    continue; // if stock is low else continue to next line
            }
        }
    }
    //  Loop Iteration ends and the controls transfers to this if statement if no product was found with low stock this below statement will run otherwise skips
    if (!found_low_stock)
        cout << endl
             << "\nAll Products from each Category have sufficient Stock!\n";
    system("pause");
    return found_low_stock;
}

//                  Just to show the Products stored in different categories if Admin wants
int show_products_lists()
{
    char any_other;
    // Loop to chk products of each file according to Admin's selection
    do
    {
        system("cls");
        cout << "-------------------------------------- View Products Window -------------------------------------------" << endl;
        system("pause");
        Category_Information selection = category_selection();
        string filename = selection.file_path;
        ifstream reading(filename.c_str());
        if (!reading)
        {
            cout << "File cannot be opened or doesn't exists ";
            return 1;
        }
        else
        {
            string line;
            system("cls");
            cout << "\nExisting Products in this Category are: \n"
                 << endl;
            cout << left << setw(12) << "ID" << setw(35) << "Name" << setw(10) << "Price" << setw(8) << "Stock\n"
                 << endl;
            while (getline(reading, line))
            {
                cout << line << endl
                     << endl;
            }
        }
        reading.close();
        cout << "Do you want to see list of Products in any other category (Y/N): ";
        cin >> any_other;
    } while (any_other != 'N' && any_other != 'n');
}

/****************************************************************************************************************************************************
 *******************************               CUSTOMER FUNTION & it's Related Previleges                  ******************************************
 ****************************************************************************************************************************************************/
//                   Customer Main Page, Login Interface and previleges Window (intial steps a customer has to follow)
int customer()
{
    //                  Checking For Authorization First
    bool Proceed_or_not;
    char other_task;
    Proceed_or_not = customer_login();

    //                  If Authorization returns TRUE
    if (Proceed_or_not == true)
    {
        // First setting the currency mode to be used in the whole program whether showing the prices of product on screen
        system("cls");
        cout << "--------------------------------------- Currency Mode Setting ------------------------------------------" << endl;
        currencytype();
        cout << "currency mode set!" << "\n"
             << endl;
        system("pause");
    ReShow_Previleges:
        //              Asking for the Action Customer wants to Perform
        system("cls");
        cout << "----------------------------- Customer Interface ------------------------------------------" << endl;
        customer_previleges();
        char customer_choice;
        cin >> customer_choice;
        switch (customer_choice) // Selecting based on the users demand
        {
        case 'P':
        case 'p':
            shopping_interface();
            break;
        case 'C':
        case 'c':
            show_cart();
            break;
        case 'S':
        case 's':
            settings();
            break;
        case 'E':
        case 'e':
            exit(0);
        default:
            cout << "\nInvalid Input!\n";
            break;
        }
        goto ReShow_Previleges;
    }
    //                          If Authorization Returns FALSE means customer is unable to login
    else
    {
        cout << "\nFailed to log in to the Customer Shopping Interface. Returning to main menu." << endl;
        system("pause");
        return 1;
    }
}

void customer_previleges()
{
    cout << "\nSelect Any one thing from the folllowing menu :\n"
         << "Shop Products    \t P " << endl
         << "Show Cart List   \t C" << endl
         << "Settings         \t S" << endl
         << "Exit             \t E" << endl
         << "\nYOur Choice: ";
}

bool customer_login()
{
//                  use of goto statement for the flow
now_login:
    system("cls");
    cout << "--------------------------- Customer Login Interface --------------------------------------" << endl;
    //                  Opening the file in read-only mode
    cout << "\nChoose your MEthod" << endl
         << "Method      \t\t Keyword" << endl
         << "Login       \t\t    L" << endl
         << "SignUp      \t\t    S" << endl
         << "\n Your Choice: ";
    char choice;
    cin >> choice;
    if (choice == 'l' || choice == 'L')
    {
        int guesses_validation = 5;
        // this function will read the customer's information stored in the file
        customer_data();
    ask_again:
        // ignoring and emptying the input buffer that leaves junk "\n" after the data is entered by user
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter your name: "; // asking for customers credentials
        string Name;
        getline(cin, Name);
        for (char &n : Name) // replacing the spaces with '-' for better handling on files
            if (n == ' ')
                n = '-';
        cout << "\nEnter Password: ";
        string Password;
        getline(cin, Password);
        cout << "\nEnter your Unique Authorization: ";
        string Auth;
        getline(cin, Auth);
        for (char &A : Auth) // same as above
            if (A == ' ')
                A = '-';
        //                    Using a loop to to check the authorizations and if it customer data exists returning true
        for (int i = 0; i < Cus.Name.size(); i++)
        {
            if (Name == Cus.Name[i] && Password == Cus.Password[i] && Auth == Cus.Authentication[i])
            {
                cout << "\nYou are an authorized Personnel\n";
                system("pause");
                customername = Name;
                return true;
            }
        }
        //              if not found in the file after searching reducing the input counter and displaing a selection msg
        guesses_validation--;
        cout << "\nThe Credentials you entered are Either Wrong or doesn't exist!" << endl;
        cout << "You have " << guesses_validation << " chances left!" << endl;
        if (guesses_validation > 0)
        {
            cout << "What will you do now! " << endl
                 << "T / t  --->   Try Again one more time" << endl
                 << "Q / q  --->   Just go back to the first menu\n"
                 << endl;
        enter_again:
            cout << "You want to DO: ";
            char do_he;
            cin >> do_he;
            if (do_he == 'T' || do_he == 't')
            { //                Proceeding according to the users input
                if (guesses_validation > 0)
                    goto ask_again;
            }
            else if (do_he == 'Q' || do_he == 'q')
            {
                return false;
            }
            else
            {
                cout << "Invalid Input!\n"
                     << endl;
                goto enter_again;
            }
        }
        else
        {
            cout << "\n Guess Chances Reached Zero!\n";
            return false;
        }
    }
    else if (choice == 'S' || choice == 's')
    {
        make_new_account();
        goto now_login;
    }
    else
    {
        cout << "\nInvalid Input\n Please Try Again\n\n";
        goto now_login;
    }
}

int make_new_account()
{
    system("cls");
    cout << "--------------------------- Make a new Account ----------------------------------------- " << endl
         << "\nEnter the details asked! " << endl;
    // Reading Customer's data first before making the new account
    customer_data();
    // Opening the file in append mode to add new customers data into file -- pointer/cursor will be auto set to last of file
    ofstream writeintofile("D:\\coding\\C++_Project\\Project Related FIles\\Logins\\Customer Login.txt", ios::app);
    if (!writeintofile)
    {
        cout << "\nFile cannot be opened or doesn't exists!" << endl;
        return 1;
    }
    else
    {
        //              To carefully handle the Input so nothing junk should be taken in by getline() function
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //          This Part has goto control that will work only if countered and how it'll be countered is written
    enter_name:
        // This Part reads the name and will compare so user name must be unique and mustn't intercept causing confusion at login window
        cout << endl
             << "Enter your Name: ";
        string name;
        getline(cin, name);
        for (char &n : name)
            if (n == ' ')
                n = '-';
        for (int i = 0; i < Cus.Name.size(); i++)
        {
            if (name == Cus.Name[i])
            {
                cout << "This User Name Already Exists. Please try a different one\n";
                goto enter_name;
                break;
            }
        }
    ask_input: // double checking and making sure the user enters correct password both times
        cout << "\nSet your Password: ";
        string password;
        getline(cin, password);
        cout << "\nDouble check you Password: ";
        string passcheck;
        getline(cin, passcheck);
        if (password != passcheck)
        {
            cout << "\nBoth passwords doesn't match correctly!\n Write Again\n"
                 << endl;
            goto ask_input;
        }
        // Unique Identification of the customer without this user will not be able to login
        cout << "\nSet your Personal IDENTIFICATION key (Ex. Coding Master)";
        string authorization;
        getline(cin, authorization);
        for (char &n : authorization)
            if (n == ' ')
                n = '-';
        writeintofile << left << setw(35) << name << setw(30) << password << setw(30) << authorization << endl; // writing into the file (details of new customer)
        writeintofile.close();
        cout << endl
             << "CONGRATULATIONS " << name << "\nYour Account has been successfully made!" << endl
             << "You will be directed back to login page......" << endl;
        system("pause");
    }
}

// A Seperate function That'll Read the customer Data Regardless of signup or Login So that we can Make the Customer's name to be Unique
void customer_data()
{
    ifstream reading("D:\\coding\\C++_Project\\Project Related FIles\\Logins\\Customer Login.txt");
    if (!reading)
    { // checking if the file opened correctly
        cout << "\nCustomer Can't be Read\n!";
        return;
    }
    else
    { //          Clearing any junk data stored in the vectors of Struct container
        Cus.Name.clear();
        Cus.Password.clear();
        Cus.Authentication.clear();
        //                          Some variables declared & Initialized for the login purpose
        string line, name, password, auth;
        while (getline(reading, line))
        {                            // Reading the whole file that contains the information of every Customer
            stringstream READ(line); // breaking a long string into chunks
            READ >> name >> password >> auth;
            Cus.Name.push_back(name);
            Cus.Password.push_back(password);
            Cus.Authentication.push_back(auth);
        }
        reading.close(); // closing the file
    }
}

// if user wants to update his password but will work only after the login is successful
void settings()
{
    system("cls");
    string line, name, auth, password, passcheck, old_pass, pre_pass;
    string temp_customername = "", temp_name = "";
    cout << "-------------------------------- Account settings ------------------------------------" << endl;
    string filename = "D:\\coding\\C++_Project\\Project Related FIles\\Logins\\Customer Login.txt";
    string tempfile = "D:\\coding\\C++_Project\\Project Related FIles\\Logins\\temp.txt";
    while (true)
    {

        cout << "\nOperation       \t\tKeyword\n"
                "Change Password     \t\tP"
             << endl
             << "Update Authorization\t\tA" << endl
             << "Nothing             \t\tN" << endl
             << "\nYour choice: ";
        char op_choice;
        cin >> op_choice;
        if (op_choice == 'N' || op_choice == 'n')
            break;
        ifstream reading_file(filename.c_str());
        ofstream writing_file(tempfile.c_str());
        if (!reading_file || !writing_file)
        {
            cout << "It seems that there's an Unprecedented Issue\nPlease Come again Later anytime we'll fix this ASAP\n";
            return;
        }
        //                      Converting the customers name into lowercase to make sure error can be avoided customername is globalvariable
        temp_customername.clear();
        for (char c : customername)
            temp_customername += tolower(c);
        //                      Reading the file line by line that contains the information about the customers
        while (getline(reading_file, line))
        {
            stringstream parsing(line); //  parsing each line one by one and
            parsing >> name >> old_pass >> auth;
            //              Also converting that same name into lowercase so make sure errors can be avoided.
            temp_name.clear();
            for (char c : name)
                temp_name += tolower(c);
            //              finding the exact line where customers data exists in the file
            if (temp_customername == temp_name)
            {                                          // if found then
                cout << "\nEnter your old password: "; // asking the customer for old password
                cin >> pre_pass;

                if (pre_pass != old_pass)
                { // if fails to enter correct detail
                    cout << "Wrong password! Cannot update.\n";
                    writing_file << left << setw(35) << name << setw(30) << old_pass << setw(30) << auth << endl;
                    continue;
                }
                //              If he enters corrects details
                if (op_choice == 'P' || op_choice == 'p')
                { // checking validation entry of user
                // UPDATE PASSWORD
                enter_again:
                    cout << "Enter new password: ";
                    cin >> password;
                    cout << "Re-enter new password: ";
                    cin >> passcheck;

                    if (passcheck != password)
                    { // checking if both entries are correct or not
                        cout << "Passwords do not match!\n Make sure you enter both of them correct";
                        goto enter_again; // if not then go back to enter_again
                    }
                    else
                    {
                        writing_file << left << setw(35) << customername << setw(30) << password << setw(30) << auth << endl;
                        cout << "Password Updated Successfully!\n";
                    }
                }
                else if (op_choice == 'A' || op_choice == 'a')
                {
                // UPDATE AUTHORIZATION
                auth_again:
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter new authorization: ";
                    getline(cin, password);
                    cout << "Re-enter new authorization: ";
                    getline(cin, passcheck);

                    if (passcheck != password)
                    {
                        cout << "Authorization values do not match!\nMake sure both of them are correct\n";
                        goto auth_again;
                    }
                    else
                    {
                        writing_file << left << setw(35) << name << setw(30) << old_pass << setw(30) << password << endl;
                        cout << "Authorization Updated Successfully!\n";
                    }
                }
            }
            else
            {
                // Write normal user unchanged
                writing_file << left << setw(30) << name << setw(30) << old_pass << setw(30) << auth << endl;
            }
        }

        reading_file.close();
        writing_file.close();

        remove(filename.c_str());
        rename(tempfile.c_str(), filename.c_str());

        cout << "\nDo you want to perform another operation? (Y/N): ";
        char again;
        cin >> again;
        if (again == 'N' || again == 'n')
            break;
    }
}

//                          Primary work of the Customer (shopping, Viewing Cart and Proceeding to the checkout)
int shopping_interface()
{
    char exit_not;
    ;
    do
    {
        system("cls");
        // Opening the file according to the Customers selection
        cout << "--------------------------------------- Shopping and Adding to Cart---------------------------------------" << endl;
        Category_Information selection = category_selection();
        string file_to_open = selection.file_path;
        ifstream Readfile(file_to_open.c_str());
        system("cls");
        if (!Readfile)
        {
            cout << "Error Opening the file ";
            return 1;
        }
        else
        {
            string line, ID, Name;
            double Price;
            int Stock;
            // showing the file onto the screen
            cout << left << setw(12) << "Product ID" << setw(35) << "Product Name" << setw(15) << "Price" << setw(15) << "Stock Available\n"
                 << endl;
            cout << "---------------------------------------------------------------------------------------\n"
                 << endl;
            while (getline(Readfile, line))
            {
                stringstream line_parsing(line);
                line_parsing >> ID >> Name >> Price >> Stock;
                cout << left << setw(12) << ID << setw(35) << Name << setw(15) << fixed << setprecision(2) << currency(Price) << setw(8) << Stock << endl
                     << endl;
            }
            Add_to_Cart(file_to_open);
        }
        cout << left << setw(40) << "\n\nShop More from any other Category" << setw(15) << "Press Y" << endl;
        cout << left << setw(40) << "To Exit" << setw(15) << "Press E" << endl
             << "Your Choice: ";
        cin >> exit_not;
    } while (exit_not != 'E' && exit_not != 'e');
    return 0;
}

//                  Adding products to the Cart
Cart Add_to_Cart(string const &file_to_open)
{
    string Cus_ID;
    char another_product, mul_items;
    static int cart_uphold = 0;
    // if the cart_uphold is below the Cart Uphold Limit variable named as --> CustomerCart.cart_UL
    if (cart_uphold < CustomerCart.cart_UL)
    {
        // Loop to add multiple products in a single go
        do
        {
            // take input of the product by ID that user wants to purchase ---- id is case insensitive means ce-1 will be auto converted to --> CE-1
            cout << "Enter Product by ID you want to add into your Cart: ";
            cin >> Cus_ID;
            for (char &c : Cus_ID)
                c = toupper(c);
            ifstream Readfile(file_to_open.c_str());
            if (!Readfile)
            {
                cout << "Error: Cannot Add Products of this Category to the Cart!\n";
            }
            else
            {
                string line, ID, name;
                double price;
                int stock, defalt = 1;
                while (getline(Readfile, line))
                {
                    stringstream parsing(line);
                    parsing >> ID >> name >> price >> stock;
                    // find the line on which the product information is stored and make sure the stock isn't zero to avoid errors
                    if (ID == Cus_ID && stock != 0)
                    {
                        cout << "\nThe Product You Have Selected is " << name << endl; // displays which product is selected by Customer
                    enter_again:
                        cout << "\nDo you want multiple items? (Y/N) "; // asks for multiple items or not
                        cin >> mul_items;
                        if (mul_items == 'Y' || mul_items == 'y')
                        {
                            cout << "\nTell Us, how many items you need of this Product: ";
                            cin >> defalt;
                            if (defalt > stock) // this will chk for the validity of the items with stock present in inventory
                            {
                                cout << "Unfotunately, we don't have that much Items!" << endl
                                     << "Please Enter Again!" << endl
                                     << endl;
                                goto enter_again;
                            }
                        }
                        // this part will add the products information to the CustomerCart
                        price = currency(price);
                        double total_price = price * defalt;
                        CustomerCart.ID.push_back(ID);
                        CustomerCart.Name.push_back(name);
                        CustomerCart.price.push_back(price);
                        CustomerCart.Quantity.push_back(defalt);
                        CustomerCart.Total_price.push_back(total_price);
                        cout << "\nProduct added to the Cart!\n";
                        cart_uphold++;
                    }
                }
            }
            cout << "\nAny other Product You want to add! (Y/N): ";
            cin >> another_product;
        } while (another_product != 'N' && another_product != 'n');
        return CustomerCart;
    }
    else
    {
        cout << "\nYou've Reached the The Maximum number of items a cart can hold\n Please Go onto the the Checkout after Confirming your Cart Items!\n ";
        system("pause");
    }
}

//                  Showing the cart to user for confirmation to proceed to the Checkout
void show_cart()
{
    show_cart_items();
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "\nYou can directly Perform the Following Actions:" << endl
         << "\n    Action         \t\t Keyword " << endl
         << "\nProceed To Checkout\t\t    P " << endl
         << "\nRemove Product     \t\t    R " << endl
         << "\nGo Back            \t\t    E" << endl
         << "\nYour Choice: ";
    char choice;
    cin >> choice;
    switch (choice)
    {
    case 'P':
    case 'p':
    {
        cout << "\nProceeding to Checkout Interface!\n"
             << endl;
        system("pause");
        system("cls");
        cout << "please wait while we Generate your Receipt and storage file!\n"
             << endl;
        system("pause");
        cout << "\nHere's Your Reciept and A file has been created in our storage for later Use\n\n"
             << endl;
        bill_generation();
        exit(0);
    }
    case 'R':
    case 'r':
    {
    again:
        show_cart_items();
        remove_from_cart();
        cout << "\nAnything else you wanna remove (Y/N): ";
        char rem_not;
        cin >> rem_not;
        if (rem_not == 'Y' || rem_not == 'y')
            goto again;
        break;
    }
    case 'E':
    case 'e':
        return;
    default:
        cout << "\nInvalid Input!";
        break;
    }
}

void remove_from_cart()
{
    cout << "--------------------- Remove Something from cart ---------------------" << endl;
    cout << "\nEnter Product by ID that you want to remove from your Cart: ";
    string RM_ID;
    Cart &IS = CustomerCart;
    cin >> RM_ID;
    for (auto &c : RM_ID)
        c = toupper(c);
    int pos_of_ID = -1;
    for (int i = 0; i < CustomerCart.ID.size(); i++)
    {
        if (RM_ID == CustomerCart.ID[i])
        {
            pos_of_ID = i;
            break;
        }
    }
    if (pos_of_ID != -1)
    {
        cout << "\nYou've Selected the Product: " << IS.Name[pos_of_ID] << endl;
        cout << "\nDo You want to DO with this Product?" << setw(35)
             << "\nRemove Whole Product" << setw(10) << "Press W" << setw(35)
             << "\nRemove Some of the Quantity" << setw(10) << "press S\n";
    choice_again:
        cout << "\nYour Choice: ";
        char choice;
        cin >> choice;
        if (choice == 'W' || choice == 'w')
        {
        erase_product:
            IS.ID.erase(IS.ID.begin() + pos_of_ID);
            IS.Name.erase(IS.Name.begin() + pos_of_ID);
            IS.price.erase(IS.price.begin() + pos_of_ID);
            IS.Quantity.erase(IS.Quantity.begin() + pos_of_ID);
            IS.Total_price.erase(IS.Total_price.begin() + pos_of_ID);
        }
        else if (choice == 'S' || choice == 's')
        {
            cout << "\nEnter Number of items you want to remove of this product: ";
            unsigned int items;
            cin >> items;
            IS.Quantity[pos_of_ID] -= items;
            if (IS.Quantity[pos_of_ID] == 0)
                goto erase_product;
        }
        else
        {
            cout << "\nInvalid choice!\n";
            goto choice_again;
        }
        show_cart_items();
        cout << "\nThe Product has been successfully Removed/Updated from the Cart!\n"
             << endl;
    }
    else
    {
        cout << "\nProduct Not found!";
    }
}

//              Generating Receipt bill for the Customer and saving it with users name into database for
void bill_generation()
{
    Cart &IS = CustomerCart;
    double sum_price = 0;
    char disc;
    string directory = "D:\\coding\\C++_Project\\Project Related FIles\\Purchase Reports\\";
    directory = directory + customername + ".txt";
    ofstream making_Reciept(directory.c_str(), ios::app);

    // Fetch System Date When the Purchase Happened
    time_t now = time(0);
    tm *now_ptr = localtime(&now);
    char date_today[20];
    strftime(date_today, sizeof(date_today), "%d-%m-%Y", now_ptr);

    //                                      First Printing on the Console
    cout << "\n\n"
         << endl;
    cout << "\nCustomer Name: " << customername << endl
         << "Date Of Purchase: " << date_today << endl;
    cout << "--------------------------------------------------------------------------------- " << endl;
    cout << "------------------ Items Bought! -----------------------" << endl
         << "--------------------------------------------------------------------------------- " << endl;
    cout << left << setw(35) << "NAME" << setw(15) << "PRICE" << setw(15) << "QUANTITY" << setw(15) << "TOTAL PRICE" << endl;
    for (int i = 0; i < CustomerCart.ID.size(); i++)
    {
        cout << left << setw(35) << IS.Name[i] << setw(15) << fixed << setprecision(2) << IS.price[i] << setw(15) << IS.Quantity[i] << setw(15) << IS.Total_price[i] << endl;
        sum_price += IS.Total_price[i];
    }
    cout << "\nEnd of List!" << endl
         << "--------------------------------------------------------------------------------- " << endl
         << "Grand Total: " << fixed << setprecision(2) << sum_price << endl;
    cout << endl
         << "--------------------------------------------------------------------------------- " << endl;
apply_discounts:
    cout << "\nDo you have a discount coupon (Y/N): ";
    cin >> disc;
    if (disc == 'Y' || disc == 'y')
    {
        int applied = discounts(sum_price);
        if (applied == 1)
            goto apply_discounts;
    }
    else
        cout << endl
             << "--------------------------------------------------------------------------------- " << endl
             << "\t\tTHANKS FOR SHOPPING FROM US!\t\t" << endl
             << "--------------------------------------------------------------------------------- ";
    cout << "\nYour Reciept has been Generated Successfully!\n"
         << endl
         << "Thanks for Shopping From Us!\n";

    //              Writing the data into a file to make a reciept with customers name after asking for discount coupon on Console
    making_Reciept << "\n\n"
                   << endl;
    making_Reciept << "\nCustomer Name: " << customername << endl
                   << "Date Of Purchase: " << date_today << endl;
    making_Reciept << "--------------------------------------------------------------------------------- " << endl;
    making_Reciept << "------------------ Items Bought! -----------------------" << endl
                   << "--------------------------------------------------------------------------------- " << endl;
    making_Reciept << left << setw(35) << "NAME" << setw(15) << "PRICE" << setw(15) << "QUANTITY" << setw(15) << "TOTAL PRICE" << endl;
    for (int i = 0; i < CustomerCart.ID.size(); i++)
    {
        making_Reciept << left << setw(35) << IS.Name[i] << setw(15) << fixed << setprecision(2) << IS.price[i] << setw(15) << IS.Quantity[i] << setw(15) << IS.Total_price[i] << endl;
    }
    making_Reciept << fixed << setprecision(2) << "\nEnd of List!" << endl
                   << "--------------------------------------------------------------------------------- " << endl
                   << "Grand Total: " << sum_price << endl
                   << "\nTotal Discount Given: " << disc_given << endl
                   << "\nGrand Price After Discount: " << grand_price << endl;
    making_Reciept << endl
                   << "--------------------------------------------------------------------------------- " << endl;
    making_Reciept << endl
                   << "--------------------------------------------------------------------------------- " << endl
                   << "\t\tTHANKS FOR SHOPPING FROM US!\t\t" << endl
                   << "--------------------------------------------------------------------------------- ";
    making_Reciept.close();

    cout << "\nA COPY of your Reciept has been Saved Successfully in our storage!\n"
         << endl;
    cout << "\nJust some little steps to be done and you're good to go!\n"
         << endl;
    discount_Reveal_criteria(grand_price);
    system("pause");

    //                            Appending data into Sales Report SO Admin can check it
    ofstream Sales("D:\\coding\\C++_Project\\Project Related FIles\\Sales Reports\\Sales.txt", ios::app);
    if (grand_price == 0)
        Sales << left << setw(7) << "Name: " << setw(35) << customername << setw(13) << "Grand_Total: " << fixed << setprecision(2) << setw(15) << sum_price << setw(15)
              << "Currency Type: " << setw(15) << CurrencyType << setw(13) << "Date & Time: " << date_today << endl;
    else
        Sales << left << setw(7) << "Name: " << setw(35) << customername << setw(13) << "Grand_Total: " << fixed << setprecision(2) << setw(15) << grand_price << setw(15)
              << "Currency Type: " << setw(15) << CurrencyType << setw(13) << "Date & Time: " << date_today << endl; 
    Sales.close();

    //                  Updating the stock after the purchase of each category Customer had shopped in
    updating_stock_after_Purchase();
    cout << "\nNow exiting the Program!\n";
    system("pause");
}

void updating_stock_after_Purchase()
{
    // loop to control the number of items present in the file
    for (int i = 0; i < CustomerCart.ID.size(); i++)
    {
        string purchasedID = CustomerCart.ID[i];
        string file;
        string prefix = purchasedID.substr(0, purchasedID.find('-')); // breaking string into smaller chunk to find its category

        // CHecking which category the product is from and opening that exact file
        if (prefix == "CE")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Computer and Electronics.txt";
        else if (prefix == "BV")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Beverages.txt";
        else if (prefix == "KA")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Kitchen Accessories.txt";
        else if (prefix == "DH")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\DIY and Hardware.txt";
        else if (prefix == "SPO")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Sports and Outdoors.txt";
        else if (prefix == "BE")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Bedroom Equipment.txt";
        else if (prefix == "SB")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Stationery and Books.txt";
        else if (prefix == "BWE")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Bathroom Equipment.txt";
        else if (prefix == "BPC")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Beauty and Personal Care.txt";
        else if (prefix == "PF")
            file = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Perfumes and Fragrances.txt";

        // making a tempfile in the same directory for the users
        string tempfile = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\temp.txt";
        // Opening the exact category file and the temporarily made file
        ifstream read(file.c_str());
        ofstream write(tempfile.c_str());

        // reading the category file to target the exact product of that category and overwriting it into temp file with that same order
        string line, ID, Name;
        double price;
        int stock;
        while (getline(read, line))
        {
            stringstream overwrite(line);
            overwrite >> ID >> Name >> price >> stock;
            if (ID == purchasedID)
            {
                stock -= CustomerCart.Quantity[i];
                if (stock < 0)
                    stock = 0;
            }
            write << left << setw(12) << ID << setw(35) << Name << setw(10) << price << setw(8) << stock << endl;
        }
        // closing both files and removing the outdated category file and renaming the new temporary file with the outdated category file name
        read.close();
        write.close();
        remove(file.c_str());
        rename(tempfile.c_str(), file.c_str());
    }
}

/****************************************************************************************************************************************
 *****************************************       Universal USE OF FUNCTIONS              ************************************************
 ****************************************************************************************************************************************/
Category_Information category_selection()
{ // struct function to return two things using the same function
    // declaring a variable and making an instance of a struct container
    int Category_choice;
    Category_Information CI;
    category_showing(); // showing category list to the user
    while (true)
    {
        cout << "\nEnter your choice: "; // taking the users input and deciding the outcome based on switch
        cin >> Category_choice;
        switch (Category_choice)
        {
        case 1:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Computer and Electronics.txt";
            CI.Short_Code = "CE";
            return CI;
        }
        case 2:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Beverages.txt";
            CI.Short_Code = "BV";
            return CI;
        }
        case 3:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Kitchen Accessories.txt";
            CI.Short_Code = "KA";
            return CI;
        }
        case 4:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\DIY and Hardware.txt";
            CI.Short_Code = "DH";
            return CI;
        }
        case 5:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Sports and Outdoors.txt";
            CI.Short_Code = "SPO";
            return CI;
        }
        case 6:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Bedroom Equipment.txt";
            CI.Short_Code = "BE";
            return CI;
        }
        case 7:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Stationery and Books.txt";
            CI.Short_Code = "SB";
            return CI;
        }
        case 8:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Bathroom Equipment.txt";
            CI.Short_Code = "BWE";
            return CI;
        }
        case 9:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Beauty and Personal Care.txt";
            CI.Short_Code = "BPC";
            return CI;
        }
        case 10:
        {
            CI.file_path = "D:\\coding\\C++_Project\\Project Related FIles\\Categories\\Perfumes and Fragrances.txt";
            CI.Short_Code = "PF";
            return CI;
        }
        default:
            cout << "\nInvalid Input!" << endl;
        }
    }
}

// just the list of the categories in the store
void category_showing()
{
    cout << "\nSelect Product Category: " << endl
         << "\nCategories       \t\t  Keyword " << endl
         << "\nComputer and Electronics     \t   1" << endl
         << "\nBeverages        \t\t   2" << endl
         << "\nKitchen Accessories \t\t   3" << endl
         << "\nDiy & Hardware         \t\t   4" << endl
         << "\nSports and Outdoors \t\t   5" << endl
         << "\nBedroom Equipment       \t   6" << endl
         << "\nStationery and Books     \t   7" << endl
         << "\nBath/Wash-room Equipmment  \t   8" << endl
         << "\nBeauty and Personal Care   \t   9" << endl
         << "\nPerfumes and Fragrances      \t   10" << endl;
}

void currencytype()
{
    cout << "Before moving further,\nPlease tell us in what currency would you like to see products prices and bills?\n"
         << "Note: The selection can only be made between USD / EURO / PKR(default)\n"
         << endl
         << "Currency" << setw(20) << "keyword" << endl
         << "USD     " << setw(20) << " 1" << endl
         << "Euro    " << setw(20) << " 2" << endl
         << "PKR     " << setw(20) << " 3" << endl;
enter_again:
    cout << "\nYour Choice: ";
    int choice;
    cin >> choice;
    if (choice != 1 && choice != 2 && choice != 3)
    {
        cout << "\nInvalid Input! Please try Again: ";
        goto enter_again;
    }
    else
    {
        switch (choice)
        {
        case 1:
            currencymode = 282.52;
            CurrencyType = "Dollars";
            break;
        case 2:
            currencymode = 329.55;
            CurrencyType = "Euro";
            break;
        case 3:
            currencymode = 1;
            CurrencyType = "PKR";
            break;
        default:
            cout << "Unknown Error Occurred, Please try once again \n"
                 << endl;
            goto enter_again;
        }
    }
}

double currency(double price)
{
    return price / currencymode;
}

// a part of function named Update_products() to overwrite the information of the product like name, price, and stock(always be added cannot be overwritten)
products updation(const products &product)
{ // parameter means taking a reference from the original container but not changing anything from it
    char choice;
    int stock;
    products Updated = product;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "\nDo you want to Rewrite Product Name(Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "\nEnter Updated Name: ";
        cin.ignore();
        getline(cin, Updated.name);
        for (char &name : Updated.name) // replacing the blank spaces with '-' for better handling afterwards
            if (name == ' ')
                name = '-';
    }
    cout << "\nDo you want to Change Product Price(Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "Updated Price: ";
        cin >> Updated.price;
    }
    cout << "\nDo you want to Add more Stock(Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y')
    {
        cout << "Stock Addition: ";
        cin >> stock;
        Updated.stock += stock;
    }
    return Updated;
}

// DISCOUNT Application and Reveal Criteria
int discounts(double sum_price)
{
    string discount_code = "";
    string filename = "D:\\coding\\C++_Project\\Project Related FIles\\Discount Codes\\Discount & promo Codes.txt";
    string temp_file = "D:\\coding\\C++_Project\\Project Related FIles\\Discount Codes\\temporary.txt";

    ifstream read_codes(filename);
    ofstream write_codes(temp_file);

    if (!read_codes || !write_codes)
    {
        cout << "Sorry Discounts cannot be applied Right Now! please Try Next Time!\n";
        return 0;
    }
    cout << "\nPlease Enter your Discount Coupon: ";
    cin >> discount_code;

    bool found = false;
    bool applied = false;

    string line, code_name;
    double discount_gives;
    unsigned int avail;
    while (getline(read_codes, line))
    {
        stringstream parsing_string(line);
        parsing_string >> code_name >> discount_gives >> avail;
        if (discount_code == code_name && avail != 0)
        {
            found = true;
            disc_given = sum_price * (discount_gives / 100);
            grand_price = sum_price - disc_given;
            cout << fixed << setprecision(2) << "\nTotal Discount Given: " << disc_given << endl
                 << "\nGrand Price After Discount: " << grand_price << endl;
            avail--;
            write_codes << left << setw(30) << code_name << setw(15) << discount_gives << setw(15) << avail << endl;
            applied = true;
        }
        else if (discount_code != code_name && avail != 0)
        {
            write_codes << left << setw(30) << code_name << setw(15) << discount_gives << setw(15) << avail << endl;
        }
    }
    write_codes.close();
    read_codes.close();
    if (!found)
    {
        cout << "\nDiscount code is Invalid!\n";
        remove(temp_file.c_str());
        return 1;
    }

    if (applied)
    {
        remove(filename.c_str());
        rename(temp_file.c_str(), filename.c_str());
        return 0;
    }
}

void discount_Reveal_criteria(double const &grand_sum)
{
    string filename = "D:\\coding\\C++_Project\\Project Related FIles\\Discount Codes\\Discount & promo Codes.txt";
    ifstream read_codes(filename.c_str());
    vector<string> coupons;
    if (!read_codes)
    {
        cout << "\nSorry Looks like discounts Application might have some Issues";
        return;
    }
    else
    {
        string line, code_name;
        double discount_gives;
        unsigned int avail;
        while (getline(read_codes, line))
        {
            stringstream parsing_string(line);
            parsing_string >> code_name >> discount_gives >> avail;
            coupons.push_back(code_name);
        }
        double price = currency(25000);
        if (grand_sum > price)
        {
            srand(time(0));
            int rand_index = rand() % coupons.size() - 1;
            cout << "For Purchasing over " << price << ", Equivalent to Rs 25000,\nYou've Won a discount coupon to be used next time: " << endl
                 << coupons[rand_index];
            cout << endl
                 << "\nMake Sure to Remeber this also the wording in Lower & Upper case" << endl;
        }
    }
}

// functions that will show real-time changes made by either Admin  or Customer on cart
void Re_show_products(string const &filename)
{
    system("cls");
    cout << "\nExisting Products in this Category are: \n"
         << endl;
    cout << left << setw(12) << "ID" << setw(35) << "Name" << setw(10) << "Price" << setw(8) << "Stock\n"
         << endl;
    cout << "------------------------------------------------------------------------\n"
         << endl;
    ifstream readfile(filename.c_str());
    string line;
    while (getline(readfile, line))
    {
        cout << line << endl
             << endl;
    }
    readfile.close();
}

void show_cart_items()
{
    system("cls");
    double t_price = 0;
    cout << "-------------------------------- Shopping Cart List ----------------------------------\n"
         << endl;
    cout << left << setw(12) << "ID" << setw(35) << "NAME" << setw(10) << "PRICE" << setw(15) << "QUANTITY" << setw(10) << "TOTAL PRICE" << endl;
    for (int i = 0; i < CustomerCart.ID.size(); i++)
    {
        cout << left << setw(12) << CustomerCart.ID[i] << setw(35) << CustomerCart.Name[i] << setw(10) << CustomerCart.price[i]
             << setw(15) << CustomerCart.Quantity[i] << setw(10) << CustomerCart.Total_price[i] << endl;
        t_price += CustomerCart.Total_price[i];
    }
    cout << "\nTotal Price is " << t_price << endl;
    cout << "\nEnd of Cart List\n"
         << endl;
}

void re_show_discounts(string const &filename)
{
    system("cls");
    ifstream read;
    read.open((filename.c_str()));
    cout << "Discount or promo codes are:\n";
    string line;
    cout << "------------------------------------------------------------------------------\n"
         << endl;
    cout << left << setw(35) << "Code" << setw(20) << fixed << setprecision(2) << "Discount gives" << setw(20) << "Avail chances" << endl
         << endl;
    while (getline(read, line))
    {
        string code;
        double disc_gives;
        int avail;
        stringstream parse(line);
        parse >> code >> disc_gives >> avail;
        cout << left << setw(35) << code << setw(20) << fixed << setprecision(2) << disc_gives << setw(20) << avail << endl
             << endl;
    }
    read.close();
}
