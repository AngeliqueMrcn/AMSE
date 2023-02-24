#include <stdio.h>

typedef struct {
   float voltage;
   float current;
   float speed;
} DCMotor;

void controlMotor(DCMotor* motor, float voltage) {
   float resistance = 1.0; // résistance de l'induit
   float inductance = 0.5; // inductance de l'induit
   float dt = 0.01; // pas de temps
   float torque = (voltage - motor->current * resistance) / inductance; // calcul du couple
   float acceleration = torque; // l'accélération est proportionnelle au couple
   motor->speed += acceleration * dt; // mise à jour de la vitesse
   motor->current += torque / inductance * dt; // mise à jour du courant
}

int main() {
   DCMotor leftMotor = {0.0, 0.0, 0.0}; // initialisation du moteur gauche
   DCMotor rightMotor = {0.0, 0.0, 0.0}; // initialisation du moteur droit
   
   // boucle de simulation
   for (int i = 0; i < 1000; i++) {
      controlMotor(&leftMotor, uL); // contrôle du moteur gauche
      controlMotor(&rightMotor, uR); // contrôle du moteur droit
      
      // affichage des grandeurs de sortie
      printf("Moteur gauche : vitesse = %f, courant = %f\n", leftMotor.speed, leftMotor.current);
      printf("Moteur droit : vitesse = %f, courant = %f\n", rightMotor.speed, rightMotor.current);
   }
   
   return 0;
}
