#include <pthread.h>
#include "caltrain.h"



void station_init(struct station *station)
{
	pthread_mutex_init(&station->mutex, NULL);

    pthread_cond_init(&station->train_arrived, NULL);
	pthread_cond_init(&station->passenger_seated, NULL);

	station->onboarding_passengers=0;
    station->waiting_passengers = 0;
    station->empty_seats = 0;

}

void station_load_train(struct station *station, int count)
{
	pthread_mutex_lock(&station->mutex);
	station->empty_seats = count;
	while (station->empty_seats > 0 && station-> waiting_passengers > 0){
        pthread_cond_broadcast(&station->train_arrived);
        pthread_cond_wait(&station->passenger_seated, &station->mutex);
	}
	station->empty_seats=0;
	pthread_mutex_unlock(&station->mutex);
}

void station_wait_for_train(struct station *station)
{
	pthread_mutex_lock(&station->mutex);
	station->waiting_passengers++;
	
	while(station->onboarding_passengers == station->empty_seats){
        pthread_cond_wait(&station->train_arrived , &station->mutex);
	}

	station->onboarding_passengers++;
	station->waiting_passengers--;
	
	pthread_mutex_unlock(&station->mutex);
	
}

void station_on_board(struct station *station)
{
	pthread_mutex_lock(&station->mutex);
	station->empty_seats--;
	station->onboarding_passengers--;

	if((station->empty_seats == 0) || (station->onboarding_passengers == 0 &&
        station->waiting_passengers == 0)){
        pthread_cond_signal(&station->passenger_seated);
	}


	pthread_mutex_unlock(&station->mutex);
}
