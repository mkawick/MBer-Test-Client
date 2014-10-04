// TestRelogin.cpp

#include "../../../Mber/ServerStack/BaseClientLibrary/ClientNetworkWrapper.h"
#include <conio.h>
#pragma warning (disable: 4996)
#include <iostream>
#include <iomanip>
#include <ctime>
#include <assert.h>

using namespace Mber;
using namespace std;
#include "NotificationCallbacks.h"

void  ListTestRelogin ()
{
   cout << "Keys:" << endl;
   cout << " l- login with random user" << endl;
   cout << " f- fast login" << endl;
   cout << " o- logout " << endl;
   cout << " c- login with crap password " << endl;
   cout << " esc- exit " << endl;

   cout << " enter- clear screen" << endl;
}


///////////////////////////////////////////////////////////////////////////////////
//void     RunTestRelogin( NetworkLayerExtended& network, NotificationsDeterministic& notify, UserAccoun* listOfAccounts, int numAccounts );
void     RunTestRelogin( NetworkLayerExtended& network, NotificationsDeterministic& notify, const char* location, UserAccount* listOfAccounts, int numAccounts )
{
   cout << "RunTestRelogin " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail, userPassword, userName;

   int standardTab = 12;

   ListTestRelogin ();

   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }

      if( key )
      {
         //network.addp
       /*  if( key == 'l' )
         {
            if( network.IsConnected() == false )
            {
               cout << "Reconnecting... hit l again in a sec or two" << endl;
               network.RegisterCallbackInterface( &notify );
               network.Init( location );
            }
            else if( triedLogin == false && network.IsReadyToLogin() == true )
            {
               int index = rand() % numAccounts;
                  userEmail = listOfAccounts[index].userEmail, 
                  userPassword = listOfAccounts[index].password, 
                  userName = listOfAccounts[index].userName;

               network.RequestLogin( userEmail, userPassword, "En" );
               triedLogin = true;

               cout << "Attempt login" << endl;

               cout <<  " userEmail: " << userEmail << endl;
               cout <<  " userPassword: " << userPassword << endl;
               cout <<  " userName: " << userName << endl;
            }
            else
            {
               cout << " not ready to login" << endl;
            }
         }*/
         if( key == 'f' )
         {
            int len = network.GetUsername().size();
            if( network.IsConnected() == false || len == 0 )
            {
               cout << "Reconnecting... hit f again in a sec or two" << endl;
               network.RegisterCallbackInterface( &notify );
               //network.RegisterCallbackInterface( &notify );
               network.Init( location );

               int index = 4;//rand() % numAccounts;

               userEmail = listOfAccounts[index].userEmail, 
               userPassword = listOfAccounts[index].password, 
               userName = listOfAccounts[index].userName;

               network.RequestLogin( userEmail, userPassword, "En" );
               triedLogin = true;

               cout << "Attempt login" << endl;

               cout <<  " userEmail: " << userEmail << endl;
               cout <<  " userPassword: " << userPassword << endl;
               cout <<  " userName: " << userName << endl;
            }
            else
            {
               cout << " not ready to login" << endl;
            }
         }
         if( key == 'b' )
         {
            cout << "Bad login" << endl;
            cout << "Reconnecting... hit b again in a sec or two" << endl;
            network.RegisterCallbackInterface( &notify );
            //network.RegisterCallbackInterface( &notify );
            network.Init( location );

            int index = rand() % numAccounts;
               userEmail = listOfAccounts[index].userEmail, 
               userPassword = listOfAccounts[index].password, 
               userName = listOfAccounts[index].userName;

            network.RequestLogin( userEmail, userPassword, "En" );
            triedLogin = true;

            cout << "Attempt login" << endl;

            cout <<  " userEmail: " << userEmail << endl;
            cout <<  " userPassword: " << userPassword << endl;
            cout <<  " userName: " << userName << endl;
         }
         if( key == 'o' )
         {
            cout << " logout request " << endl;
            cout << " ---------------------- " << endl;
            network.RequestLogout();
            network.Exit();
            triedLogin= false;
         }

         if( key == 'c' )
         {
            cout << " c- login with crap password " << endl;
            int len = network.GetUsername().size();
            if( network.IsConnected() == false || len == 0 )
            {
               //cout << "Reconnecting... hit c again in a sec or two" << endl;
               network.RegisterCallbackInterface( &notify );
               //network.RegisterCallbackInterface( &notify );
               network.Init( location );

               int index = 4;//rand() % numAccounts;

               userEmail = listOfAccounts[index].userEmail, 
               userPassword = "abc123[]", 
               userName = listOfAccounts[index].userName;

               network.RequestLogin( userEmail, userPassword, "En" );
               triedLogin = true;

               cout << "Attempt login" << endl;

               cout <<  " userEmail: " << userEmail << endl;
               cout <<  " userPassword: " << userPassword << endl;
               cout <<  " userName: " << userName << endl;
            }
            else
            {
               cout << " not ready to login" << endl;
            }
         }
         
  
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListTestRelogin ();
         }
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 100 );
   }

   getch();
   network.Exit();
}

///////////////////////////////////////////////////////////////////////////////////
