/* 
 * File:   SessionOrganizer.h
 * Author: Kapil Thakkar
 *
 */

#ifndef SESSIONORGANIZER_H
#define	SESSIONORGANIZER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>


#include "Conference.h"
#include "Track.h"
#include "Session.h"

using namespace std;


/**
 * SessionOrganizer reads in a similarity matrix of papers, and organizes them
 * into sessions and tracks.
 * 
 * @author Kapil Thakkar
 *
 */
class SessionOrganizer {
private:
    double ** distanceMatrix;

    int totalTracks ;
    int papersInSession ;
    int sessionsInTrack ;

    Conference *conference;

    double processingTimeInMinutes ;
    double tradeoffCoefficient ; // the tradeoff coefficient


public:
    SessionOrganizer();
    SessionOrganizer(string filename);
    
    
    /**
     * Read in the number of parallel tracks, papers in session, sessions
     * in a track, and the similarity matrix from the specified filename.
     * @param filename is the name of the file containing the matrix.
     * @return the similarity matrix.
     */
    void readInInputFile(string filename);
    
    
    
    /**
     * Organize the papers according to some algorithm.
     */
    void organizePapers();


       /**
     * Generates a greedy random scheduling for the conference.
     */
    void greedyRandomState();


    /**
     * Finds the first index in the Distance Matrix that has min difference from the
     * given paper
     */
    int FindIndex(double a, int index);


    /**
     * Compares two doubles.
     */
    bool DoubleCompare(double a, double b);


    /**
     * First index that isn't yet scheduled.
     */
    int FirstFreeIndex (int arr[]);


    /**
     * Generates a random scheduling for the conferene.
     */
    void randomState();


    /**
     * Swaps two papers.
     */
    void swap(int sessionIndex1, int paperIndex1, int sessionIndex2, int paperIndex2);


    /**
     * Finds goodness of the schedule if the swap is carried out.
     */
    double findGoodness(int sessionIndex1, int paperIndex1, int sessionIndex2, int paperIndex2);


    /**
     * Finds the likeliness of a given paper with a given session.
     */
    double findLikeliness(int track, int session, int paper, int paperId);

    /**
     * Finds the distance of a given paper from a given session.
     */
    double findDistance(int track, int session, int paper, int paperId);


    /**
     * Compares the heuristic of all possible neighbours and updates to the best
     */
    bool findAndUpdateNeighbour();
 
    
    /**
     * Get the distance matrix.
     * @return the distance matrix.
     */
    double** getDistanceMatrix();
    

    /**
     * Sets a 2D array for the likes and dislikes.
    */
    void compatibility();


    /**
     * Finds the likeliness for a given session
    */
    int likeliness(int track, int session);


    /**
     * Finds the conflict between two sessions
    */
    int conflict(int track1, int session1, int track2, int session2);

    /**
     * Score the organization.
     * @return the score.
     */
    double scoreOrganization();
    
    
    void printSessionOrganiser(char *);
};

#endif	/* SESSIONORGANIZER_H */

