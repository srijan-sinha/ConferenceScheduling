/* 
 * File:   Conference.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "Conference.h"

Conference::Conference ( )
{
    this->totalTracks = 0;
    this->sessionsInTrack = 0;
    this->papersInSession = 0;
}

Conference::Conference ( int totalTracks, int sessionsInTrack, int papersInSession )
{
    this->totalTracks = totalTracks;
    this->sessionsInTrack = sessionsInTrack;
    this->papersInSession = papersInSession;
    initTracks ( totalTracks, sessionsInTrack, papersInSession );
}

void Conference::initTracks ( int totalTracks, int sessionsInTrack, int papersInSession )
{
    tracks = ( Track * ) malloc ( sizeof (Track ) * totalTracks );
    for ( int i = 0; i < totalTracks; i++ )
    {
        Track tempTrack ( sessionsInTrack );
        for ( int j = 0; j < sessionsInTrack; j++ )
        {
            Session tempSession ( papersInSession );
            tempTrack.setSession ( j, tempSession );
        }
        tracks[i] = tempTrack;
    }
}

int Conference::getTotalTracks ( )
{
    return totalTracks;
}

int Conference::getSessionsInTrack ( )
{
    return sessionsInTrack;
}

int Conference::getPapersInSession ( )
{
    return papersInSession;
}

Track Conference::getTrack ( int index )
{
    if ( index < totalTracks )
    {
        return tracks[index];
    }
    else
    {
        cout << "Index out of bound - Conference::getTrack" << endl;
        exit ( 0 );
    }
}

void Conference::setPaper ( int trackIndex, int sessionIndex, int paperIndex, int paperId )
{
    if ( this->totalTracks > trackIndex )
    {
        Track curTrack = tracks[trackIndex];
        curTrack.setPaper ( sessionIndex, paperIndex, paperId );
    }
    else
    {
        cout << "Index out of bound - Conference::setPaper" << endl;
        exit ( 0 );
    }
}

double Conference::getGoodness()
{
    return goodness;
}

void Conference::setGoodness(double value)
{
    goodness = value;
}

void Conference::printConference (char * filename )
{
    ofstream ofile(filename);

    for ( int i = 0; i < totalTracks; i++ )
    {
        for ( int j = 0; j < sessionsInTrack; j++ )
        {
            for ( int k = 0; k < papersInSession; k++ )
            {
                ofile<< tracks[i].getSession ( j ).getPaper ( k ) << " ";
            }
            if ( j != sessionsInTrack - 1 )
            {
                ofile<<"| ";
            }
        }
        ofile<<"\n";
    }
    ofile.close();
    cout<<"Organization written to ";
    printf("%s :)\n",filename);

}

void Conference::print()
{
    for ( int i = 0; i < totalTracks; i++ )
    {
        for ( int j = 0; j < sessionsInTrack; j++ )
        {
            for ( int k = 0; k < papersInSession; k++ )
            {
                cout<< tracks[i].getSession ( j ).getPaper ( k ) << " ";
            }
            if ( j != sessionsInTrack - 1 )
            {
                cout<<" | ";
            }
        }
        cout << "\n";
    }
}
