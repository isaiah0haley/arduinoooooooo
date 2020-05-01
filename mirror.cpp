#include <iostream>
#include <fstream>
#include <string>


using namespace std;


string dataRoot = "/home/pi/mirrorData/data/";
string picRoot = "/home/pi/mirrorData/pictures/";


string readData();
void sendImage(int selector);

void cssPrinter();
bool nearDetect();
void email();


int main()
{
	
	string date = readData();
	cout << "Content-type:text/html\r\n\r\n";
   	cout << "<html>\n";
   	cout << "<head>\n";
	cout << "<title>" +date+"</title>\n";
	cout << "<META HTTP-EQUIV=\"refresh\" CONTENT=\"15\">";
 	cout << "</head>\n";
	cout << "<style>";
	cssPrinter();
	cout << "</style>";
	cout << "<body  style=\"background-color:black;\">\n";
	if(nearDetect())
	{
   	
	 
   	cout << "<h2 class = \"box\", id = \"head\">"+date+"</h2>\n";
	cout << "<div class = \"box\", id = \"tl\">"+date+"</div>\n";
	cout << "<div class = \"box\", id = \"tr\">"+date+"</div>\n";  
	cout << "<div class = \"box\", id = \"br\">"+date+"</div>\n";  
	cout << "<div class = \"box\", id = \"bl\">"+date+"</div>\n";  

	email();
	}
   	cout << "</body>\n";
   	cout << "</html>\n";
	//sendImage(1); 
	return 0;
}


void cssPrinter()
{
	cout << ".box{";
	cout << "display: inline-block;";
	cout <<  "width: 100px;";
	cout <<  "height: 100px;";
	cout <<  "background: black;";
	cout <<  "color: white;";
	cout << "}";
	
	cout << "#head {";
	cout << "position: absolute;";
	cout << "left: 50%;";	
  	cout << "top: 50%;";
	cout << "margin-top: -50px;";
	cout << "margin-left: -50px;";
	cout <<  "background: black;";
	cout << "}";
	
	cout << "#tl {";//top left data box
	cout << "position: absolute;";
	cout << "left: 0%;";	
  	cout << "top: 0%;";
	 
	cout <<  "background: black;";
	cout << "}";
	cout << "#tr {";//top right data box
	cout << "position: absolute;";
	cout << "left: 100%;";	
  	cout << "top: 0%;";
	cout << "margin-left: -100px;";
 
	cout <<  "background: black;";
	cout << "}";
	cout << "#br {";//bottom right data box
	cout << "position: absolute;";
	cout << "left: 100%;";	
  	cout << "top: 100%;";
	cout << "margin-left: -100px;";
 	cout << "margin-top: -100px;";
	cout <<  "background: black;";
	cout << "}";
	cout << "#bl {";//bottom left data box
	cout << "position: absolute;";
	cout << "left: 0%;";	
  	cout << "top: 100%;";

 	cout << "margin-top: -100px;";
	cout <<  "background: black;";
	cout << "}";





}

bool nearDetect()
{
	ifstream usfile;	
	string pth = dataRoot + "dist.txt";
	usfile.open(pth);
	string temp;
	
	getline(usfile,temp);
	int tint = stoi(temp);
	if(tint == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}


void email()
{
	cout << "<ol>";
	cout << "<li>Coffee</li>";
	cout << "<li>Tea</li>";
	cout << "<li>Milk</li>";
	cout << "</ol>";

//	ifstream emfile;
//	emfile.open
}


void sendImage(int selector)
{
	cout << "<h2>HTML Image</h2>";
	cout << "<img src=\"/home/pi/mirrorData/pictures/flower.jpg\" alt=\"Trulli\" width=\"500\" height=\"477\">";
}

string readData()
{
	ifstream datefile;
	string pth = dataRoot + "date.txt";
	datefile.open(pth);
	string temp;
	getline(datefile, temp);
	 
	return temp;

}