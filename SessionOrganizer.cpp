/* 
 * File:   SessionOrganizer.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "SessionOrganizer.h"
#include "Util.h"


SessionOrganizer::SessionOrganizer ( )
{
    parallelTracks = 0;
    papersInSession = 0;
    sessionsInTrack = 0;
    processingTimeInMinutes = 0;
    tradeoffCoefficient = 1.0;
}

SessionOrganizer::SessionOrganizer ( string filename )
{
    readInInputFile ( filename );
    conference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
}

void SessionOrganizer::organizePapers ( )
{
    
    // initialisation with no optimisation

    int paperCounter = 0;
    for ( int i = 0; i < conference->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < conference->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < conference->getPapersInSession ( ); k++ )
            {
                conference->setPaper ( j, i, k, paperCounter);
                paperCounter++;
            }
        }
    }
    
    // randomState();
}

void SessionOrganizer::randomState ()
{
    int size = parallelTracks * sessionsInTrack * papersInSession ;
    int random = 0;
    int trackCount = 0;
    int sessionCount = 0;
    int papersCount = 0;
    int counter = 0;

    vector<int> papers;
    for (int i = 0; i < size; i++){
        papers.push_back(i);
    }  
    
    while(papers.size()!=0){
        srand(time(0));
        random = rand() % (papers.size()); 
        trackCount = counter  / ( sessionsInTrack * papersInSession);
        sessionCount = counter / ( papersInSession ) % sessionsInTrack;
        papersCount =  counter % papersInSession;
        conference->setPaper(trackCount, sessionCount, papersCount,papers.at(random)); 
        papers.erase(papers.begin() + random);
        counter ++;
    }    
    compatibility();
}

void SessionOrganizer::findAndUpdateNeighbour ()
{
    
}

void SessionOrganizer::readInInputFile ( string filename )
{
    vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {
            //cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }

    if ( 6 > lines.size ( ) )
    {
        cout << "Not enough information given, check format of input file";
        exit ( 0 );
    }

    processingTimeInMinutes = atof ( lines[0].c_str () );
    papersInSession = atoi ( lines[1].c_str () );
    parallelTracks = atoi ( lines[2].c_str () );
    sessionsInTrack = atoi ( lines[3].c_str () );
    tradeoffCoefficient = atof ( lines[4].c_str () );

    int n = lines.size ( ) - 5;
    double ** tempDistanceMatrix = new double*[n];
    for ( int i = 0; i < n; ++i )
    {
        tempDistanceMatrix[i] = new double[n];
    }


    for ( int i = 0; i < n; i++ )
    {
        string tempLine = lines[ i + 5 ];
        string elements[n];
        splitString ( tempLine, " ", elements, n );

        for ( int j = 0; j < n; j++ )
        {
            tempDistanceMatrix[i][j] = atof ( elements[j].c_str () );
        }
    }
    distanceMatrix = tempDistanceMatrix;

    int numberOfPapers = n;
    int slots = parallelTracks * papersInSession*sessionsInTrack;
    if ( slots != numberOfPapers )
    {
        cout << "More papers than slots available! slots:" << slots << " num papers:" << numberOfPapers << endl;
        exit ( 0 );
    }
}

void SessionOrganizer::compatibility  (  ) 
{
    int len = parallelTracks * sessionsInTrack;
    cout << "Total sessions: " << len << endl;
    cout << "Sessions in Track: " << sessionsInTrack << endl;
    cout << "Num Tracks: " << parallelTracks << endl;
    int track = 0;
    int session = 0;
    int pairTrack1 = 0;
    int pairTrack2 = 0;
    int pairSession1 = 0;
    int pairSession2 = 0;
    double ** tempDistanceMatrix = new double*[len];
    for(int i = 0; i < len; i++)
    {
        tempDistanceMatrix[i] = new double[len];
    }


    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j  < len; j++)
        {
            if(i == j)
            {
                track = i / sessionsInTrack;
                session = i % sessionsInTrack;
                cout<< "Call of likeliness for track: " << track << " and session: " << session << endl;
                tempDistanceMatrix[i][j] = likeliness(track, session);
            }
            else
            {
                pairTrack1 = i / sessionsInTrack;
                pairSession1 = i % sessionsInTrack;
                pairTrack2 = j / sessionsInTrack;
                pairSession2 = j % sessionsInTrack;
                cout<< "Call of conflict for track1: " << pairTrack1 << " session1: " << pairSession1 << " track2: " << pairTrack2 << " session2: " << pairSession2 << endl;
                tempDistanceMatrix[i][j] = conflict(pairTrack1, pairSession1, pairTrack2, pairSession2);
            }
        }
    }
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            cout << "i : " << i << " j : " << j << " value : " << tempDistanceMatrix[i][j]<< endl;
        }
    }
    conference->distanceMatrix = tempDistanceMatrix;
}

int SessionOrganizer::likeliness( int track, int session )
{
    int like = 0;
    int paper1 = 0;
    int paper2 = 0;
    for(int i = 0; i < papersInSession; i++)
    {
        for(int j = i+1; j < papersInSession; j++)
        {
            paper1 = conference->getTrack(track).getSession(session).getPaper(i);
            paper2 = conference->getTrack(track).getSession(session).getPaper(j);
            cout << "Paper1: " << paper1 << " Paper2: " << paper2 << endl;
            like += 1 - distanceMatrix[paper1][paper2];
        }
    }
    return like;
}

int SessionOrganizer::conflict( int track1, int session1, int track2, int session2 )
{
    int conflict = 0;
    int paper1 = 0;
    int paper2 = 0;
    for(int i = 0; i < papersInSession; i++)
    {
        for(int j = 0; j < papersInSession; j++)
        {
            paper1 = conference->getTrack(track1).getSession(session1).getPaper(i);
            paper2 = conference->getTrack(track2).getSession(session2).getPaper(j);
            cout << "Paper1: " << paper1 << " Paper2: " << paper2 << endl;
            conflict += distanceMatrix[paper1][paper2];
        }
    }
    return conflict;
}

double** SessionOrganizer::getDistanceMatrix ( )
{
    return distanceMatrix;
}

void SessionOrganizer::printSessionOrganiser ( char * filename)
{
    conference->printConference ( filename);
}

double SessionOrganizer::scoreOrganization ( )
{
    // Sum of pairwise similarities per session.
    double score1 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession = tmpTrack.getSession ( j );
            for ( int k = 0; k < tmpSession.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession.getPaper ( k );
                for ( int l = k + 1; l < tmpSession.getNumberOfPapers ( ); l++ )
                {
                    int index2 = tmpSession.getPaper ( l );
                    score1 += 1 - distanceMatrix[index1][index2];
                }
            }
        }
    }

    // Sum of distances for competing papers.
    double score2 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack1 = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack1.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession1 = tmpTrack1.getSession ( j );
            for ( int k = 0; k < tmpSession1.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession1.getPaper ( k );

                // Get competing papers.
                for ( int l = i + 1; l < conference->getParallelTracks ( ); l++ )
                {
                    Track tmpTrack2 = conference->getTrack ( l );
                    Session tmpSession2 = tmpTrack2.getSession ( j );
                    for ( int m = 0; m < tmpSession2.getNumberOfPapers ( ); m++ )
                    {
                        int index2 = tmpSession2.getPaper ( m );
                        score2 += distanceMatrix[index1][index2];
                    }
                }
            }
        }
    }
    double score = score1 + tradeoffCoefficient*score2;
    return score;
}
