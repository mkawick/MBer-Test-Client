
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

void  ListTestNotificationServer ()
{
   cout << "Keys:" << endl;

   cout << " r- request all of the devices for this game" << endl;
   cout << " g- request all of the devices for all game" << endl;
   cout << " c- changing this device.. update the properties" << endl;
   cout << " l- list all devices registered" << endl;
   cout << " n- register new device" << endl;
   cout << " m- send notification" << endl;

   cout << " s- reregister existing device" << endl;
   cout << " k- grab uuid of registered device " << endl;
   cout << " j- change audiofile of registered device " << endl;
   cout << " o- logout" << endl;
   cout << " i- login" << endl;

   cout << " enter- clear screen" << endl;

   cout << " ---------------------------- " << endl;
}

string GenerateRandomName()
{
   string newName = "mickey'";
   string randomNumber;
   int numberLength = rand() %6 + 7;
   for( int i=0; i<numberLength; i++ )
   {
      randomNumber += '0'+rand()%10;
   }
   return string ( newName + randomNumber );
}

///////////////////////////////////////////////////////////////////////////////////

void     RunTestNotificationServer( NetworkLayerExtended& network, 
                                   NotificationsDeterministic& notify, 
                                   UserAccount& account, 
                                   const char* location  )
{
   cout << "RunTestNotificationServer " << endl;
   bool triedLogin = false;
   network.EnableMultithreadedCallbackSystem();
   string userEmail = account.userEmail, 
      userPassword = account.password, 
      userName = account.userName;


   int standardTab = 12;
   bool  hasRegisteredStandardDevice  = false;

   ListTestNotificationServer ();

   string defaultDeviceName = "crap_default";
   string defaultDeviceId = "crap_default_device_id" ;
   string previousUuid = "786f414b617e3380";

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
      if( hasRegisteredStandardDevice == false && 
         network.IsLoggedIn() == true )
      {
        /* string uuid = "PLAYDEK-demo014-ipad";
         network.RegisterDevice( uuid, "", Platform_ios, uuid );*/
         hasRegisteredStandardDevice = true;
      }

      if( key )
      {
         if( key == 'n' )
         {
            cout << "registering device" << endl;
            bool result = network.RegisterDevice( "", "mickey", Platform_ios, "supercalifragilisticexpidocious"  );
         }
         if( key == 's' )
         {
            cout << endl << " reregistering device " << endl;
            int numDevices = network.GetNumDevices();
            cout << " num: " << numDevices << endl;
            if( numDevices == 0 )
            {
               cout << " no devices present" << endl;
            }
            else
            {
               RegisteredDevice device;
               network.GetDevice( rand() % numDevices , device );
              /* for( int i=0; i<numDevices; i++ )
               {
                  
                  cout << "   name: " << device.name << endl;
                  cout << "   uuid: " << device.uuid << endl;
                  cout << "   icon: " << device.iconId << endl;
                  cout << "..." << endl;
               }*/
               string newName = GenerateRandomName();
               bool result = network.RegisterDevice( device.uuid, newName, Platform_ios, "supercalifragilisticexpidocious" );

               cout << "   name: " << (newName) << endl;
               cout << "   uuid: " << device.uuid << endl;
               cout << "   icon: " << device.iconId << endl;
               cout << "..." << endl;

               cout << "----------------------------------" << endl;
            }
         }
         if( key == 'r' )
         {
            cout << "requesting devices" << endl;
            bool result = network.RequestListOfDevicesForThisGame();
         }
         if( key == 'g' )
         {
            cout << "requesting devices.. all platforms" << endl;
            bool result = network.RequestListOfDevicesForThisGame( 0 );
         }
         if( key == 'c' )
         {
            cout << " changing this device " << endl;
             int numDevices = network.GetNumDevices();
            cout << " num: " << numDevices << endl;
            if( numDevices == 0 )
            {
               cout << " no devices present" << endl;
            }
            else
            {
               RegisteredDevice device;
               network.GetDevice( rand() % numDevices , device );

               string uuid = device.uuid;//network.GetDeviceUuid();
               string newName = GenerateRandomName();
               
               bool result = network.ChangeDevice( uuid, newName, "test.aws", 0, 16, 3 );

               cout << "   name: " << newName << endl;
               cout << "   uuid: " << uuid << endl;
               cout << "..." << endl;

               cout << "----------------------------------" << endl;
            }
            
         }
         if( key == 'm' )
         {
            cout << endl << " sending notification " << endl;
            network.SendNotification( rand() %3+1, "Hello" );
         }

         if( key == 'l' )
         {
            cout << endl << " list devices " << endl;
            int numDevices = network.GetNumDevices();
            cout << " num: " << numDevices << endl;
            for( int i=0; i<numDevices; i++ )
            {
               RegisteredDevice device;
               network.GetDevice( i, device );
               cout << "   name: " << device.name << endl;
               cout << "   uuid: " << device.uuid << endl;
               cout << "   icon: " << device.iconId << endl;
               cout << "   enabled: " << boolalpha << device.isEnabled << noboolalpha << endl;
               cout << "..." << endl;
            }

            cout << "----------------------------------" << endl;
         }

         if( key == 'q' )
         {
            cout << endl << " delete device " << endl;
            int numDevices = network.GetNumDevices();
            cout << " num: " << numDevices << endl;
            for( int i=0; i<numDevices; i++ )
            {
               RegisteredDevice device;
               network.GetDevice( i, device );
               if( device.name.find( "delete" ) != std::string::npos )
               {
                  cout << "found it" << endl;
                  bool result = network.RemoveDevice( device.uuid );
                  cout << "result is " << endl;
                  cout << std::boolalpha << result << std::noboolalpha << endl;
                  break;
               }
            }
         }
         if( key == 'k' )
         {
            cout << endl << " grab uuid of registered device " << endl;
            int numDevices = network.GetNumDevices();
            cout << " num: " << numDevices << endl;
            if( numDevices == 0 )
            {
               cout << "there are no devices" << endl;
            }
            else
            {
               RegisteredDevice device;
               network.GetDevice( 0, device );
               previousUuid = device.uuid;
               cout << "Saved uuid: " << previousUuid << endl;
            }
            
         }
         if( key == 'j' )
         {
            cout << " j- change audiofile of registered device " << endl;
            int numDevices = network.GetNumDevices();
            cout << " num: " << numDevices << endl;
            if( numDevices == 0 )
            {
               cout << "there are no devices" << endl;
            }
            else
            {
               RegisteredDevice device;
               network.GetDevice( 0, device );
               cout << " uuid: " << device.uuid << endl;
               cout << " name: " << device.name << endl;
               cout << " isEnabled: " << device.isEnabled << endl;
               network.ChangeDevice( device.uuid, device.name, "newAudioFile.wav", device.isEnabled, device.iconId, 1 ); 
               /*previousUuid = device.uuid;
               cout << "Saved uuid: " << previousUuid << endl;*/
            }
         }
         if( key == 'u' )
         {
            cout << "Deleting particular device" << endl;
            int numDevices = network.GetNumDevices();
            cout << " num: " << numDevices << endl;
            for( int i=0; i<numDevices; i++ )
            {
               RegisteredDevice device;
               network.GetDevice( i, device );
               if( device.name.find( defaultDeviceName ) != std::string::npos )
               {
                  cout << "found it" << endl;
                  bool result = network.RemoveDevice( device.uuid );
                  cout << "result is " << endl;
                  cout << std::boolalpha << result << std::noboolalpha << endl;
                  break;
               }
            }
         }
         
         if( key == 'o' )
         {
            bool isConnected = network.IsConnected();
            bool isLoggedIn = network.IsLoggedIn();
            cout << " loggin user out" << endl;
            if( triedLogin == true && 
               isConnected == true &&
               isLoggedIn == true
               )
            {
               cout << "RequestLogout" << endl;
               network.RequestLogout();
               network.Exit();

            }
            else
            {
               cout << "Error: Not fully logged in" << endl;
            }
         }
         if( key == 'i' )
         {
            bool isConnected = network.IsConnected();
            bool isLoggedIn = network.IsLoggedIn();
            cout << " loggin user in" << endl;
            if( triedLogin == true && 
               network.IsConnected() == true &&
               network.IsLoggedIn() == true
               )
            {
               cout << "Error: Already logged in" << endl;
            }
            else
            {
               triedLogin = false; // resetting the flag... on the next loop, this will log you in.
               hasRegisteredStandardDevice = false;
               network.RegisterCallbackInterface( &notify );
               network.Init( location );//
            }
         }
         

        /* if( key == 'c' )
         {
            cout << "create new channel" << endl;
            string nameUuid ("user12"); // we are only dealing with user 8 and 12
            if( userEmail == "user12" )
               nameUuid = "user8";

            string chatChannelName = "TestChannel_";
            chatChannelName += GenerateUUID( 0xffffffff );
            network.CreateNewChatChannel( chatChannelName );
         }
         if( key == 'l' )
         {
            cout << " l- leave first channel in list " << endl;

            int num = network.GetNumChannels();
            cout << " num channels = " << num << endl;
            if( num == 0 )
            {
               cout << "No channels " << endl;
            }
            else
            {
               ChatChannel channel;
               network.GetChannel( 0, channel );
               network.LeaveChannel( channel.uuid );
               channel.Print();
            }
         }
         if( key == 'z' )
         {
            cout << " z- list all channels and members" << endl;
            int num = network.GetNumChannels();
            cout << " num channels = " << num << endl;
            for( int i=0; i<num; i++ )
            {
               ChatChannel channel;
               if( network.GetChannel( i, channel ) == true )
               {
                  cout << "Index: " << i << endl;
                  channel.Print();
               }
            }
         }
         if( key == 'i' )
         {
            cout << " i- invite other user to channel" << endl;
            //network.RequestListOfInvitationsSent();
            string nameUuid ("user12"); // we are only dealing with user 8 and 12
            if( userEmail == "user12" )
               nameUuid = "user8";

            int num = network.GetNumChannels();
            cout << " num channels = " << num << endl;
            if( num == 0 )
            {
               cout << "No channels " << endl;
            }
            else
            {
               ChatChannel channel;
               network.GetChannel( 0, channel );
               network.AddUserToChannel( nameUuid, channel.uuid );
               channel.Print();

               cout << "User invited: " << nameUuid << endl;
            }
         }
         if( key == 'a' )
         {
            cout << "Create new channel and add a bunch of people to it" << endl;
            //cout << " a- accept invitation to channel" << endl;
            //network.RequestListOfInvitationsSent();
            notify.localUserUuid = userName;
            for( int i=1; i<10; i++ )
            {
               if( i == 8 ) 
                  continue;
               string nameUuid ("user");
               nameUuid += '0' + i;
               notify.userToAddToChatChannelUponCallback.push_back( nameUuid );
            }

            string chatChannelName = "TestChannel_";
            chatChannelName += GenerateUUID( 0xffffffff );
            network.CreateNewChatChannel( chatChannelName );
         }*/
         if( key == 13 )// carriage return
         {
            system("cls");// ms specific
            cout << "Login:: user: " << userName << endl;
            cout << " email: " << userEmail << endl;
            cout << " pwd: " << userPassword << endl;
            cout << "--------------------------------------" << endl << endl;

            ListTestNotificationServer ();
         }
      }
      if( network.NeedsProcessingTime() )
      {
         network.UpdateNotifications();
      }
      Sleep( 30 );
   }


   network.RequestLogout();

   cout << "Logging out .. press any key to exit"  << endl;
   getch();
   network.Exit();
}

///////////////////////////////////////////////////////////////////////////////////


