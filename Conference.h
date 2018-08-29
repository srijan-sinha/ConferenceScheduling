/* 
 * File:   Conference.h
 * Author: Kapil Thakkar
 *
 * Created on 9 August, 2015, 10:07 AM
 */

#ifndef CONFERENCE_H
#define	CONFERENCE_H

#include<iostream>
#include<fstream>
using namespace std;

#include "Track.h"

class Conference {
private:

    // The array of tracks.
    Track *tracks;

    // The number of parallel tracks.
    int totalTracks;

    // The number of sessions in a track.
    int sessionsInTrack;

    // The number of papers in a session.
    int papersInSession;

    // The goodness of the schedule
    double goodness;

public:
    Conference();
    
    /**
     * Constructor for Conference.
     * 
     * @param totalTracks is the number of total tracks.
     * @param sessionsInTrack is the number of sessions in a track.
     * @param papersInSession is the number of papers in a session.
     */
    Conference(int totalTracks, int sessionsInTrack, int papersInSession);
    
    
    // The array of index of like and dislike.
    double ** distanceMatrix;
    
    
    /**
     * Initialize the tracks.
     * @param parallelTracks is the number of parallel tracks.
     * @param sessionsInTrack is the number of sessions in a track.
     * @param papersInSession is the number of papers in a session.
     */
    void initTracks(int totalTracks, int sessionsInTrack, int papersInSession);
    
    
    /**
     * Gets the number of total tracks.
     * @return the number of total tracks.
     */
    int getTotalTracks();
    
    
    /**
     * Gets the number of sessions in a track.
     * @return the number of sessions in a track.
     */
    int getSessionsInTrack();
    
    
    /**
     * Gets the number of papers in a session.
     * @return the number of papers in a session.
     */
    int getPapersInSession();
    
    
    /**
     * Gets the track at the specified index.
     * @param index is the index of the specified track.
     * @return the track
     */
    Track getTrack(int index);


    /**
     * Sets the paper in the specified slot to the given paper id.
     * @param trackIndex is the track index.
     * @param sessionIndex is the session index.
     * @param paperIndex is the paper index.
     * @param paperId is the id of the paper.
     */
    void setPaper(int trackIndex, int sessionIndex, int paperIndex, int paperId);
    

    /**
     * Returns the goodness of the conference schedule.
     */
    double getGoodness();


    /**
     * Sets the goodness of the schedule to the given value.
     */
    void setGoodness(double value);


    void printConference(char *);

    void print();
};

#endif	/* CONFERENCE_H */

