SWeb is a C++ web server that is built to be very fast and fully customizable. 

INSTALL:

To install, you need cmake, openssl, boost libraries, and a C++ compiler installed on your PC. Then you run cmake in the root folder. 

CONFIGURATION:
By default, the server looks for the certificate and key in the root folder called cert.crt and Key.key. This can be changed in the Server.h file.

The default port is set to 443. This can be changed in the Server.h file

It loads static pages from the Static folder

To add a dynamic page:
1.) Copy the ./includes/DefaultPage.h file and the ./pages/DefaultPage.cpp file. 
2.) Modify the #ifndef and #define lines in the new header file. 
3.) Change the class name to your new class in both files. 
4.) Change the routing criteria in the cpp file
5.) In the Router.cpp file, add the include file and an instance of the class to the route. 
6.) Add the cpp file to the CMAKELists.txt

To add a session variable:
1.) Add it to the session.h file

