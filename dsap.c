#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 5
#define MAX_QUEUE 10

// Movie structure
typedef struct {
char name[50];
char showtime[20];
int availableTickets;
} Movie;

// Queue structure
typedef struct {
char customerName[50];
int movieIndex;
} BookingRequest;

BookingRequest queue[MAX_QUEUE];
int front = -1, rear = -1;

// Array of movies
Movie movies[MAX_MOVIES] = {
{"Avengers: Endgame", "6:00 PM", 5},
{"Inception", "7:00 PM", 3},
{"Interstellar", "8:00 PM", 4},
{"Joker", "9:00 PM", 6},
{"The Matrix", "10:00 PM", 2}
};

// Queue Functions
int isFull() {
return (rear + 1) % MAX_QUEUE == front;
}

int isEmpty() {
return front == -1;
}

void enqueue(BookingRequest req) {
if (isFull()) {
printf("Queue is full. Cannot add more bookings.\n");
return;
}
if (isEmpty()) {
front = rear = 0;
} else {
rear = (rear + 1) % MAX_QUEUE;
}
queue[rear] = req;
printf("Booking request added to queue.\n");
}

BookingRequest dequeue() {
BookingRequest req = {"", -1};
if (isEmpty()) {
printf("No booking requests in the queue.\n");
return req;
}
req = queue[front];
if (front == rear) { // only one element
front = rear = -1;
} else {
front = (front + 1) % MAX_QUEUE;
}
return req;
}

// Display movies
void displayMovies() {
printf("\nAvailable Movies:\n");
for (int i = 0; i < MAX_MOVIES; i++) {
printf("%d. %s (%s) - Tickets: %d\n", i + 1, movies[i].name, movies[i].showtime,
movies[i].availableTickets);
}
}

// Book a ticket (add to queue)
void bookTicket() {
BookingRequest req;
printf("\nEnter your name: ");
scanf(" %[^\n]", req.customerName);

displayMovies();
printf("Select movie number: ");
scanf("%d", &req.movieIndex);
req.movieIndex--;

if (req.movieIndex < 0 || req.movieIndex >= MAX_MOVIES) {
printf("Invalid movie selection.\n");
return;
}

enqueue(req);
}

// Process next booking
void processBooking() {
if (isEmpty()) {
printf("No pending bookings to process.\n");
return;
}

BookingRequest req = dequeue();
if (movies[req.movieIndex].availableTickets > 0) {
movies[req.movieIndex].availableTickets--;
printf("\nBooking confirmed for %s to '%s' at %s.\n",
req.customerName,
movies[req.movieIndex].name,
movies[req.movieIndex].showtime);
} else {
printf("Sorry, no tickets available for '%s'.\n", movies[req.movieIndex].name);
}
}

// Main Menu
int main() {
int choice;

do {
printf("\n--- Movie Ticket Booking System ---\n");
printf("1. View Movies\n");
printf("2. Book Ticket\n");
printf("3. Process Next Booking\n");
printf("4. Exit\n");
printf("Enter choice: ");
scanf("%d", &choice);

switch (choice) {
case 1: displayMovies(); break;
case 2: bookTicket(); break;
case 3: processBooking(); break;
case 4: printf("Exiting...\n"); break;
default: printf("Invalid choice.\n");
}

} while (choice != 4);

return 0;
}


