#include <pthread.h>

struct station
{
	// mutex
	pthread_mutex_t mutex;

	// condition variables
	pthread_cond_t train_arrived;
	pthread_cond_t passenger_seated;

	int onboarding_passengers;
	int waiting_passengers;
	int empty_seats;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);