#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "com.h"
#define MESSAGES_LENGTH 10
#define PERDIOD 40 //ms
#define LIVETRACKER_PERIOD 50 //ms
namespace hal {
    typedef struct StrMessage {
        String message;
        long stamp;
    } StrMessage;

    typedef struct PositionValue  {
        float x, y, a;
        long stamp;
    } PositionValue;

    typedef struct DiffSpeedValue {
        float vl, vr;
        long stamp;
    } DiffSpeedValue;

    typedef struct SpeedValue {
        float v, w;
        long stamp;
    } SpeedValue;

    class Debug {
        public:
            Debug();
            void setMacAddress(String address) {
                macAddress = address;
            };
            void initTracker();
            void enableTracker();
            void stopTracker();
            void trackMessage(String message);
            void trackMessage(String message, long stamp);
            void debugMessage(String message);
            void printStr(String message);
            void log(String message);
            void trackPosition(float x, float y, float a, long stamp);
            void trackKPosition(float x, float y, float a, long stamp);
            void trackTrajectory(float x, float y, long stamp);
            void returnTrackerData();
            void enableDebug();
            void stopDebug();
            void checkSerial(String serialData);
            void processSerial();
            void trackOdo(float vl, float vr, float cons_vl, float cons_vr, long stamp);

            void setMaxParseTime(long value){maxParseTime = value;};
            long getMaxParseTime(){return maxParseTime;};

            void setMinParseTime(long value){minParseTime = value;};
            long getMinParseTime(){return minParseTime;};

            void enableLiveTrack(uint8_t* _trackerAddress, Com* com);
            void disableLiveTrack();
            void liveTrackSetup();
            void liveTrackMessage(String msg);

            void liveTrackPosition(float x, float y, float a, long stamp);

            
        private:
            bool debugMod = false;
            bool trackerMod = false;
            String macAddress = "";
            bool busy = false;
            StrMessage strMessages[MESSAGES_LENGTH];
            PositionValue positions[MESSAGES_LENGTH];
            PositionValue trajectory[MESSAGES_LENGTH];
            PositionValue kpositions[MESSAGES_LENGTH];
            DiffSpeedValue consign[MESSAGES_LENGTH];
            DiffSpeedValue speed[MESSAGES_LENGTH];

            long minParseTime = 0;
            long maxParseTime = 0;
            

            int sm_i = 0, pos_i = 0, kpos_i = 0, cons_i = 0, traj_i = 0, odo_i = 0;
            long sm_t = 0, pos_t = 0, kpos_t = 0, cons_t = 0, traj_t = 0, odo_t = 0;

            bool liveTrackMod = false;
            uint8_t trackerAddress[6];
            Com* com;
            long lastSendedLiveTrackTime = 0;
            TrackData liveTrackData;

    };
}

#endif