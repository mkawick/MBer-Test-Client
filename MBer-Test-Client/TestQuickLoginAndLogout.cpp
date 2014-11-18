
#include "BaseClientLibrary/ClientNetworkWrapper.h"
#include <conio.h>
#pragma warning (disable: 4996)
#include <iostream>
#include <iomanip>
#include <ctime>
#include <assert.h>

using namespace Mber;
using namespace std;
#include "NotificationCallbacks.h"


///////////////////////////////////////////////////////////////////////////////////

void     RunTestQuickLoginAndLogout( NetworkLayerExtended& network, 
                                   NotificationsDeterministic& notify, 
                                   UserAccount& account )
{
   cout << "RunTestNotificationServer " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;


   string defaultDeviceName = "crap_default";
   string defaultDeviceId = "crap_default_device_id" ;
   string previousUuid = "786f414b617e3380";
   time_t timeBeforeLogout = 0;


   int key = 0;
   while( key != 27 )// escape
   {
      key = 0;
      if( kbhit() )
      {
         key = getch();
      }

      if( triedLogin == false && 
         network.IsConnected() == true &&
         network.IsLoggedIn() == false
         )
      {
         network.RequestLogin( userEmail, userPassword, "En" );
         triedLogin = true;

         cout << "Login attempted for " << userEmail << ", pwd= " << userPassword << endl;
         //exit(0);// aggressive exit
      }
      if( network.IsLoggedIn() == true && timeBeforeLogout == 0 )
      {
         cout << "Preping for logout" << endl;
         time( &timeBeforeLogout );
      }

      if( key )
      {
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;
         }
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 100 );

      if( timeBeforeLogout )
      {
         time_t currentTime;
         time( &currentTime );
         if( difftime( currentTime, timeBeforeLogout ) > 2 )
            break;
      }
   }


   network.RequestLogout();

   network.Exit();
}

///////////////////////////////////////////////////////////////////////////////////


