#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

#include "models.h"
#include "xcurse.h"

std::vector<Item> items;
std::vector<Item> updates;
time_t t = time(NULL);
tm * timePtr = localtime(&t);

void Checkout();
void Manage();
void AddData();
void Menuawal();
void DisplayData();
void DeleteData();
void Quit();
void UpdateData();


void Tentang(){
	std::cout << "credit";
}

void load_data()
{
	std::ifstream is("items.csv");
	
	std::string item;
	while(std::getline(is, item))
	{
		int begin = 0;
		int pos = item.find(",");
		std::string id = item.substr(begin, pos);
		
		begin = pos + 1;
		pos = item.find(",", begin);
		std::string name = item.substr(begin, pos - begin);
		
		begin = pos + 1;
		std::string price = item.substr(begin);
		
		items.push_back({id, name, stod(price)});
	}
	
	is.close();
}

void show_data(int col, int item_row)
{
	xc::color(0, 7);
	xc::xy(col, item_row);
		
	for(auto i : items)
	{
		xc::xy(col, item_row++);
		std::cout << std::setw(5) << i.id;
		std::cout << std::setw(17) << i.name;
		std::cout << std::setw(8) << i.price;
		std::cout << ' ' << std::endl;
	}
	
	xc::color(7, 0);
	xc::xy(col, item_row);
	
	std::cin.get();
}

Item find_data(std::string id)
{
	for(auto i : items)
		if(i.id == id)
			return i;
		
	return Item{"", "", 0};
}

void print_bill(std::vector<DetailTransaction> details)
{
	std::ofstream os("bill.txt");
	DetailTransaction bayar;
	
	os << "(|********************************************|)" << std::endl;
	os << "(|--------------------------------------------|)" << std::endl;
	os << "(|    +                                  +    |)" << std::endl;
	os << "(|    +	  ------- Toko  Yu-Sum -------   +    |)" << std::endl;
	os << "(|    +	  -------- YOGYAKARTA --------   +    |)" << std::endl;
	os << "(|    +                                  +    |)" << std::endl;
	os << "(|--------------------------------------------|)" << std::endl;
	os << "(|     "<<(timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900;
	os << "                     ";
	os << (timePtr->tm_hour) << ":" <<(timePtr->tm_min)<<  "    |)" << std::endl;
	os << "(|--------------------------------------------|)" << std::endl;
	
	double total = 0;
	for(DetailTransaction d : details)
	{
		double sub = d.qty * d.item.price;
		total += sub;
		os <<"(|  " <<std::setiosflags(std::ios::left) << std::setw(42) << d.item.name;
		os << "|)";
		os << std::endl;
		os << "(|  "<<std::setiosflags(std::ios::right)<< std::setw(3) << d.qty;
		os <<std::setw(3) << "x";
		os << std::setw(11) << d.item.price;
		os << std::setw(22) << sub;
		os << "   |)";
		os << std::resetiosflags(std::ios::right)<<std::endl;
	}
	os << "(|--------------------------------------------|)" << std::endl;
	os << std::setiosflags(std::ios::left) << std::setw(19) << "(|";
	os << std::setw(14) << "Total Harga :";
	os <<std::setiosflags(std::ios::right)<< std::setw(10) << total << "   |)"<< std::endl <<std::resetiosflags(std::ios::right);
	os << "(|--------------------------------------------|)" << std::endl;
	os << "(|  Instagram : @YUSUM_FRUITS                 |)" << std::endl;
	os << "(|  Phone     : 0879837213475                 |)" <<std::endl;
	os << "(|--------------------------------------------|)" << std::endl;
	os << "(|    $--- Terima Kasih  Telah Mampir ---$    |)" << std::endl;
	os << "(|       $--- TIDAK MENERIMA RETUR ---$       |)" << std::endl;
	os << "(|********************************************|)" << std::endl;

	
	os.close();
	
	/*system("start /min notepad /p bill.txt");*/
}

// ----- User Interface -----

int colpts[] = {4, 10, 44, 52, 58};
int rowpts[] = {1, 8, 10, 29, 32};
bool repeat = true;



void draw_form()
{
	bool loop = true;

    
	system("cls");
    xc::xy(18, 3); std::cout << "++++++++++++++++++++++++++++++++++++++";
	xc::xy(18, 4); std::cout << "+    ----- Toko Buah Yu Sum -----    +";
	xc::xy(18, 5); std::cout << "+  --- MURAH - SEGAR - ISTIMEWA ---  +";
	xc::xy(18, 6); std::cout << "++++++++++++++++++++++++++++++++++++++";
   xc::xy(2, 31); std::cout << " |------------------------------------------------------------------| ";
	xc::xy(2, 32); std::cout << " |     $--- Terima Kasih Sudah Berbelanja di Toko Kami ---$         |";
	xc::xy(2, 33); std::cout << " |------------------------------------------------------------------|";
	xc::xy(2, 34); std::cout << " |      C = Credit | F = Check ID | M = Manage Data | ! = EXIT      |";
	xc::xy(2, 35); std::cout << " |******************************************************************|";
    xc::xy(colpts[0], rowpts[2]); std::cout << " ID";
	xc::xy(colpts[1], rowpts[2]); std::cout << " Name";
	xc::xy(colpts[2], rowpts[2]); std::cout << " Price";
	xc::xy(colpts[3], rowpts[2]); std::cout << " QTY";
	xc::xy(colpts[4], rowpts[2]); std::cout << " sub";

	
			xc::xy(4, rowpts[3] - 1);
	std::cout  <<std::setw(48) << "Total  :";
	
    xc::xy(4, rowpts[3] );
	std::cout  <<std::setw(48) << "Pay  :";

    xc::xy(4, rowpts[3] + 1);
	std::cout  <<std::setw(48) << "Change:";
	for(auto i = rowpts[2]; i <= rowpts[3] - 2; i++ )
        {
            
            xc::xy(colpts[0] - 1, i); std::cout <<char(179);
            xc::xy(colpts[1] -1, i); std::cout << char(179);            
            xc::xy(colpts[2] - 1, i); std::cout <<char(179);
            xc::xy(colpts[3] - 1, i); std::cout <<char(179);
            xc::xy(colpts[4] - 1, i); std::cout <<char(179);

            xc::xy(70, i); std::cout << char(179);
            
            xc::xy(3, rowpts[2] - 1); std::cout << char(218);
            xc::xy(3, rowpts[2] + 1); std::cout << char(195);
            xc::xy(70, rowpts[2] + 1); std::cout << char(180);
            xc::xy(70, rowpts[2] - 1); std::cout << char(191);
            xc::xy(3, rowpts[3] - 2 ); std::cout << char(192);
            xc::xy(70, rowpts[3] - 2 ); std::cout << char(217);
            xc::xy(9  , rowpts[2]+ 1); std::cout << char(197);
        }
	for(auto i = colpts[0] ; i <= colpts[4] + 11; i++)
        {
            xc::xy(i, rowpts[0] + 1); std::cout << char(196);
            xc::xy(i, rowpts[1] - 1); std::cout << char(196);
            xc::xy(i, rowpts[1] + 1); std::cout << char(196);            
            xc::xy(i, rowpts[2] - 1); std::cout << char(196);
            xc::xy(i, rowpts[2] + 1); std::cout << char(196);
            xc::xy(i, rowpts[3] - 2); std::cout << char(196);

            
        }
	  xc::xy(9  , rowpts[2]+ 1); std::cout << char(197);
            xc::xy(43  , rowpts[2]+ 1); std::cout << char(197);
            xc::xy(51  , rowpts[2]+ 1); std::cout << char(197);
            xc::xy(57  , rowpts[2]+ 1); std::cout << char(197);
            xc::xy(9, rowpts[2] - 1 ); std::cout << char(194);
            xc::xy(43, rowpts[2] - 1 ); std::cout << char(194);
            xc::xy(51, rowpts[2] - 1 ); std::cout << char(194);
            xc::xy(57, rowpts[2] - 1 ); std::cout << char(194);
            xc::xy(9, rowpts[3] - 2); std::cout << char(193);
            xc::xy(43, rowpts[3] - 2); std::cout << char(193);
            xc::xy(51, rowpts[3] - 2); std::cout << char(193);
            xc::xy(57, rowpts[3] - 2); std::cout << char(193);
    
}

void input_form()
{
	
	system("cls");
	draw_form();
	
	double sub = 0;
	double total = 0;
	std::vector<DetailTransaction> details;
	
	while(true)
	{
		std::time_t now = std::time(0);
        std::tm *local = std::localtime(&now);

        local->tm_hour -= 12;
        
        xc::xy(58, 8);std::cout   <<(timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900;
        
		auto item_row = rowpts[2] + 2;
		
		for(auto d:details)
		{
			xc::xy(colpts[0], item_row); std::cout << d.item.id;
			xc::xy(colpts[1] + 1, item_row); std::cout << d.item.name;
			xc::xy(colpts[2] +1 , item_row); std::cout  << d.item.price;
			xc::xy(colpts[3] + 1, item_row); std::cout  << d.qty;
			sub = d.item.price * d.qty;
			xc::xy(colpts[4] + 1, item_row); std::cout << std::setw(9) << sub;
			++item_row;
		}
		
		total += sub;
		xc::xy(colpts[4], rowpts[3] - 1); std::cout << std::setw(9) << total;
		
		form:
		xc::xy(colpts[0], item_row);
		std::string id;
		std::getline(std::cin, id);
		
		if(id == "!")
			return;
		 
		/*if(id == GetAsyncKeyState(VK_F7))
			{
				Tentang();
			}
		*/
		
		if(id == "#")
		{
			repeat = false;
			return;
		}
		

		
		if(id == "")
			break;
			
		Item i = find_data(id);
		if(id != i.id )
			{ MessageBox(NULL, "Wrong Value\nInsert The Right Value","WARNING", MB_OK);
			 goto form;}
			
		if(i.id == "")
			continue;
	
		
		
		double qty = 1;
		
		xc::xy(colpts[1] + 1, item_row); std::cout << i.name;
		xc::xy(45, item_row); std::cout << i.price;
		xc::xy(53, item_row); std::cout << qty;
		
		std::string in_qty;	
		xc::xy(53, item_row);
		getline(std::cin, in_qty);
		if(in_qty != "")
			qty = stod(in_qty);
			
		details.push_back({{i.id, i.name, i.price}, qty});
	}
	
	xc::color(10, 0);
	xc::xy(58, 29);
	
	std::string in_pay;
	std::getline(std::cin, in_pay);
	
	if(in_pay == "!")
		return;
	
	DetailTransaction bayar;
	double pay;
	bayar.pay = stod(in_pay);
	xc::xy(colpts[4], rowpts[3] ); std::cout << std::setw(9) << bayar.pay;
	
	xc::color(14, 0);
	xc::xy(colpts[4], rowpts[3] + 1); std::cout << std::setw(9) << bayar.pay - total;
	
	print_bill(details);
	
	xc::xy(colpts[0], rowpts[3]); 
	xc::color(7, 0); std::cout << "Press ";
	xc::color(0, 7); std::cout << " ENTER ";
	xc::color(7, 0); std::cout << " to continue.";
	
	std::cin.get();
	Menuawal();
}

void do_transaction()
{
	while(repeat)
		input_form();
	
	system("cls");
}



void Quit(){
system("cls");
std::cout << " |******************************************************************|\n";
std::cout << " |------------------------------------------------------------------|\n";
std::cout << " |              +                                    +              |\n";
std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n";
std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n";
std::cout << " |              +                                    +              |\n";
std::cout << " |------------------------------------------------------------------|\n";
std::cout << " |                 -TERIMA KASIH SUDAH BERBELANJA-                  |\n";
std::cout << " |                         - HORMAT  KAMI -                         |\n";
std::cout << " |                                                                  |\n";
std::cout << " |    |-----|   |   |     ---      |-    |     |  --     |----      |\n";
std::cout << " |       |      |___|    |_ _|     |  -  |     |-        |___       |\n";
std::cout << " |       |      |   |    |   |     |    -|     |-            |      |\n";
std::cout << " |       |      |   |    |   |     |     |     |  --     ----|      |\n";
std::cout << " |                                                                  |\n";
std::cout << " |------------------------------------------------------------------|\n";
std::cout << " |  instagram : @YUSUM_FRUITS                Phone : 0879837213475  |\n";
std::cout << " |------------------------------------------------------------------|\n";
std::cout << " |                                                                  |\n";
std::cout << " |------------------------------------------------------------------|\n";
std::cout << " |******************************************************************|\n";
}

void LoadData(){

    std::ifstream is("items.csv");
	
	std::string update;
	while(std::getline(is, update))
	{
		int begin = 0;
		int pos = update.find(",");
		std::string id = update.substr(begin, pos);
		
		begin = pos + 1;
		pos = update.find(",", begin);
		std::string name = update.substr(begin, pos - begin);
		
		begin = pos + 1;
		std::string price = update.substr(begin);
		
		updates.push_back({id, name, stod(price)});
	}
	
	is.close();
}
void UpdateData();

void UpdateData(){
    system("cls");
    LoadData();

  xc::xy(2,1 ); std::cout << " |******************************************************************|\n";
  xc::xy(2,2 ); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,3 ); std::cout << " |              +                                    +              |\n";
  xc::xy(2,4 ); std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n";
  xc::xy(2,5 ); std::cout << " |              +   (||  MURAH-SEGAR-ISTIMEWA  ||)   +              |\n";
  xc::xy(2,6 ); std::cout << " |              +                                    +              |\n";
  xc::xy(2,7 ); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,8 ); std::cout << " |	    ! Ubah Data !                                             |\n";
  xc::xy(2,9 ); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,10 ); std::cout << " |     Masukkan PK yang ingin di ubah  :                            |\n";
  xc::xy(2, 11); std::cout << " |       ID    : _____________                                      |\n";
  xc::xy(2,12 ); std::cout << " |       Nama  : _____________                                      |\n";
  xc::xy(2,13 ); std::cout << " |       Harga : _____________                                      |\n";
  xc::xy(2,14 ); std::cout << " |                                                                  |\n";
  xc::xy(2,15 ); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,16 ); std::cout << " |  instagram : @YUSUM_FRUITS                Phone : 0879837213475  |\n";
  xc::xy(2,17 ); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,18 ); std::cout << " |          $--- Selamat Datang dan Selamat bebelanja ---$          |\n";
  xc::xy(2,19 ); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,20 ); std::cout << " |******************************************************************|\n";

    std::ofstream os("temp.txt");
    int l, m;
    xc::xy(43, 10);
    std::string harga, k;
    std::getline(std::cin, k);
    if(k == ""){
        Manage();
    }
    //else {
      //  MessageBox(NULL, "Harap DIISI sesaui dengan primarry key yang ada", "Warning!!", MB_OK);
      //  UpdateData();
  //  }
    m = stoi(k);
    l = m-1;
   //std:: cin.ignore();
    xc::xy(19, 11); std::getline(std::cin,updates[l].id );
    xc::xy(19, 12); std::getline(std::cin, updates[l].name);
    xc::xy(19, 13); std::getline(std::cin, harga);
    updates[l].price = stod(harga);
    for(Item i : updates){
        os << i.id << ','<<i.name<<','<<i.price<<std::endl;
    }
    os.close();
    remove("items.csv");
    rename("temp.txt", "items.csv");
    Manage();
}

void DeleteData(){
    system("cls");
  xc::xy(2,1 );std::cout << " |******************************************************************|\n";
  xc::xy(2,2 );std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,3 );std::cout << " |              +                                    +              |\n";
  xc::xy(2,4 );std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n";
  xc::xy(2,5 );std::cout << " |              +   (||  MURAH-SEGAR-ISTIMEWA  ||)   +              |\n";
  xc::xy(2,6 );std::cout << " |              +                                    +              |\n";
  xc::xy(2,7 );std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,8 );std::cout << " |      ! Hapus Data !                                              |\n";
  xc::xy(2,9 );std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,10 );std::cout << " |           Masukkan Primarry Key(PK) yang ingin dirubah           |\n";
  xc::xy(2,11 );std::cout << " |                             PK : __                              |\n";
  xc::xy(2,12 );std::cout << " |                                                                  |\n";
  xc::xy(2,13 );std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,14 );std::cout << " |  instagram : @YUSUM_FRUITS                Phone : 0879837213475  |\n";
  xc::xy(2,15 );std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,16 );std::cout << " |          $--- Selamat Datang dan Selamat bebelanja ---$          |\n";
  xc::xy(2,17 );std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2,18 );std::cout << " |******************************************************************|\n";
    std::vector<std::string> records;
    std::string line;
    std::ifstream records_input("items.csv");//open file stream
    while(std::getline(records_input,line)){//read all the line from the file and store in vector
        records.push_back(line);
    }

    records_input.close();//close the file
    size_t recno = records.size();//get the number of line
    size_t recno1 ;

    std::string k;

    xc::xy(38, 11);
    std::getline(std::cin, k);
    	int re;
	re = stoi(k);
    if( re < 1 | re < 0)
    {
        MessageBox(NULL, "Maaf Mohon Masukkan Primary Key dengan benar", "Warning!!", MB_OK);
        DeleteData();
    }
    recno = re -1;
    records.erase(records.begin() + recno1);//delete user choise
    recno = records.size();//the size of the vector will change
    
    std::ofstream records_output("items.csv");
    for(size_t i = 0; i < recno; i++){
        records_output << records[i] << std::endl;
    }
    xc::xy(2,12 );std::cout << " |                ALL DONE!! Press Enter to continue                |\n";
    xc::xy(55, 12);
    std::cin.get();
    Manage();
}

void AddData(){
  system("cls");
  xc::xy(2, 1); std::cout << " |******************************************************************|\n";
  xc::xy(2, 2); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 3); std::cout << " |              +                                    +              |\n";
  xc::xy(2, 4); std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n";
  xc::xy(2, 5); std::cout << " |              +   (||  MURAH-SEGAR-ISTIMEWA  ||)   +              |\n";
  xc::xy(2, 6); std::cout << " |              +                                    +              |\n";
  xc::xy(2, 7); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 8); std::cout << " |   ! Tambah Data !                                                |\n";
  xc::xy(2, 9); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 10); std::cout << " |                                                                  |\n";
  xc::xy(2, 11); std::cout << " |   ID       : _____                                               |\n";
  xc::xy(2, 12); std::cout << " |   Nama     : _____                                               |\n";
  xc::xy(2, 13); std::cout << " |   Harga    : _____                                               |\n";
  xc::xy(2, 14); std::cout << " |                                                                  |\n";
  xc::xy(2, 15); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 16); std::cout << " |  instagram : @YUSUM_FRUITS                Phone : 0879837213475  |\n";
  xc::xy(2, 17); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 18); std::cout << " |        Masukkan Kata KEMBALI pada tabel id untuk kembali         |\n";
  xc::xy(2, 19); std::cout <<" |------------------------------------------------------------------|\n";
  xc::xy(2, 20); std::cout <<" |******************************************************************|\n";
  
  std::fstream stud;
  stud.open("items.csv", std::ios::app);
  std::string id, name, price;
  
  while(true){
   xc::xy(18, 11); std::cout << "_____";
    xc::xy(18, 12); std::cout << "___________________";
xc::xy(18, 13); std::cout << "_____";
   xc::xy(18, 11);std::getline(std::cin, id);
  if(id == "")
    {break;
    Manage();}
  

  xc::xy(18, 12); std::getline(std::cin, name);
  
  xc::xy(18, 13);std::getline(std::cin, price);
  stud<<id<<','<<name<<','<<price<<'\n';
  }
    stud.close();
}

void DisplayData(){
    system("cls");
xc::xy(2,1 ); std::cout << " |******************************************************************|\n ";
xc::xy(2, 2); std::cout << " |------------------------------------------------------------------|\n ";
xc::xy(2, 3); std::cout << " |              +                                    +              |\n ";
xc::xy(2, 4); std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n ";
xc::xy(2,5 ); std::cout << " |              +   (||  MURAH-SEGAR-ISTIMEWA  ||)   +              |\n ";
xc::xy(2,6 ); std::cout << " |              +                                    +              |\n ";
xc::xy(2,7 ); std::cout << " |------------------------------------------------------------------|\n ";
xc::xy(2,8 ); std::cout << " | PK | ID   | Nama                                   | Harga       |\n ";
xc::xy(2, 9); std::cout << " |------------------------------------------------------------------|\n ";

  
    char id [30], name [30], price[30];
    int i = 1;
    int z = 10;
    std::fstream stud;
    stud.open("items.csv", std::ios::in);
    while(!stud.eof()){
        stud.getline(id,30,',');
        stud.getline(name,30,',');
        stud.getline(price,30);
        xc::xy(3, z++);
        std::cout << "| ";
        std::cout << std::setiosflags(std::ios::left)<<std::setw(3)<< i++;
        std::cout << char(179)<<' ';
        std::cout  << std::setw(5) << id;
        std::cout << char(179)<<" ";
        std::cout << std::setw(39)<< name;
        std::cout << char(179)<< ' ';
        std::cout <<std::setw(12)<< price ;
        std::cout << "|"<<std::endl;
    }
     std::cout << "   |------------------------------------------------------------------|\n ";
 std::cout << "  |     Press Enter to back.                                         |\n ";
 std::cout << "  |------------------------------------------------------------------|\n ";
 std::cout << "  |  instagram : @YUSUM_FRUITS                Phone : 0879837213475  |\n ";
 std::cout << "  |------------------------------------------------------------------|\n ";
 std::cout << "  |          $--- Selamat Datang dan Selamat bebelanja ---$          |\n ";
 std::cout << "  |------------------------------------------------------------------|\n ";
 std::cout << "  |******************************************************************|\n ";
 
system("pause > NULL");
}
//void ShowData();
//void UpdateData();
//void RemoveData();

void Manage(){
  system("cls");
  rename("temp.txt", "items.csv");
  xc::xy(2, 1); std::cout << " |******************************************************************|\n";
  xc::xy(2, 2); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 3); std::cout << " |              +                                    +              |\n";
  xc::xy(2, 4); std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n";
  xc::xy(2, 5); std::cout << " |              +   (||  MURAH-SEGAR-ISTIMEWA  ||)   +              |\n";
  xc::xy(2, 6); std::cout << " |              +                                    +              |\n";
  xc::xy(2, 7); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 8); std::cout << " |   SILAHKAN PILIH MENU YANG ADA :                                 |\n";
  xc::xy(2, 9); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 10); std::cout << " |   1. Tambah Data                                                 |\n";
  xc::xy(2, 11); std::cout << " |   2. Lihat Data                                                  |\n";
  xc::xy(2, 12); std::cout << " |   3. Ubah Data                                                   |\n";
  xc::xy(2, 13); std::cout << " |   4. Hapus Data                                                  |\n";
  xc::xy(2, 14); std::cout << " |   5. Kembali                                                     |\n";
  xc::xy(2, 15); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 16); std::cout << " |  instagram : @YUSUM_FRUITS                Phone : 0879837213475  |\n";
  xc::xy(2, 17); std::cout << " |------------------------------------------------------------------|\n";
  xc::xy(2, 18); std::cout << " |          $--- Selamat Datang dan Selamat bebelanja ---$          |\n";
  xc::xy(2, 19); std::cout <<" |------------------------------------------------------------------|\n";
  xc::xy(2, 20); std::cout <<" |******************************************************************|\n";
  xc::xy(38, 8);
  
  std::string n;
  std::getline(std::cin, n);
  if(n == "1")
      {  AddData();}
     
    else if(n == "2")
     {   DisplayData();}
        
    else if(n == "3")
        UpdateData();
        
    else if(n == "4")
        {DeleteData();}
        
    else if (n == "5")
        Menuawal();
        
    else{
        MessageBoxA(NULL, "Wrong Input ", "Warning", MB_OK);}
        Manage();
}
void Menuawal(){
    system("cls");
    xc::xy(2, 1);; std::cout << " |******************************************************************|\n" ;
    xc::xy(2, 2);; std::cout << " |------------------------------------------------------------------|\n";
    xc::xy(2, 3);; std::cout << " |              +                                    +              |\n";
    xc::xy(2, 4);; std::cout << " |              +       (||  TOKO  YU-SUM  ||)       +              |\n";
    xc::xy(2, 5);; std::cout << " |              +   (||  MURAH-SEGAR-ISTIMEWA  ||)   +              |\n";
    xc::xy(2, 6);; std::cout << " |              +                                    +              |\n";
    xc::xy(2, 7);; std::cout << " |------------------------------------------------------------------|\n";
    xc::xy(2, 8);; std::cout << " |   SILAHKAN PILIH MENU YANG ADA :                                 |\n";
    xc::xy(2, 9);; std::cout << " |------------------------------------------------------------------|\n";
    xc::xy(2, 10);; std::cout << " |  1. Manage barang                                                |\n";
    xc::xy(2, 11);; std::cout << " |  2. Checkout                                                     |\n";
    xc::xy(2, 12);; std::cout << " |  3. Keluar                                                       |\n";
    xc::xy(2, 13);; std::cout << " |------------------------------------------------------------------|\n";
    xc::xy(2, 14);; std::cout << " |  instagram : @YUSUM_FRUITS                Phone : 0879837213475  |\n";
    xc::xy(2, 15);; std::cout << " |------------------------------------------------------------------|\n";
    xc::xy(2, 16);; std::cout << " |          $--- Selamat Datang dan Selamat bebelanja ---$          |\n";
    xc::xy(2, 17);; std::cout << " |------------------------------------------------------------------|\n";
    xc::xy(2, 18);; std::cout << " |******************************************************************|\n";
    
    xc::xy(38, 8);
    
    std::string input ;
    
    std::getline(std::cin, input);
     if(input == "1")
        Manage();
     else if(input == "2")
        do_transaction();
     else if(input == "3")
        Quit();
     else
            {MessageBoxA(NULL,"WRONG INPUT !!!!", "Warning",  MB_OK);}

    
}