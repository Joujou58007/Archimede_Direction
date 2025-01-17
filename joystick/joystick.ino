#include <Servo.h> // Inclure la bibliothèque Servo

// Définition des catégories sous forme d'entiers (ou utilisez des énumérations si vous préférez)
#define FULL_GAUCHE 5
#define HALF_GAUCHE 4
#define AUCUN_MOUVEMENT 3
#define HALF_DROITE 2
#define FULL_DROITE 1
#define OUT_OF_RANGE 0


// Définition des broches du joystick (axes X et Y)
const int joystickXPin = A0;  // Axe X connecté à la broche analogique A0
const int joystickYPin = A1;  // Axe Y connecté à la broche analogique A1

const int UPPER_LEFT_SERVO_PORT = 11;
const int UPPER_RIGHT_SERVO_PORT = 10;
const int DOWN_RIGHT_SERVO_PORT = 9;
const int DOWN_LEFT_SERVO_PORT = 6;

// Servo myServo; // Créer un objet Servo
Servo UpperLeftServo;
Servo UpperRightServo;
Servo DownRightServo;
Servo DownLeftServo;

void setup() {
  // Démarrer la communication série
  Serial.begin(9600);

  // Connecter les servomoteurs aux branches 11, 10, 9 et 6
  UpperLeftServo.attach(UPPER_LEFT_SERVO_PORT);
  UpperRightServo.attach(UPPER_RIGHT_SERVO_PORT);
  DownRightServo.attach(DOWN_RIGHT_SERVO_PORT);
  DownLeftServo.attach(DOWN_LEFT_SERVO_PORT);
}

void loop() {
  // Lire les valeurs des axes X et Y du joystick (plage : 0 à 1023)
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);

  // Catégoriser les valeurs du joystick pour l'axe X et l'axe Y
  int movementCategoryX = categorizeMovement(joystickXValue);
  int movementCategoryY = categorizeMovement(joystickYValue);

  // Afficher les catégories de mouvement sur le moniteur série
  Serial.print("Movement Category X: ");
  Serial.print(movementCategoryX);
  Serial.print("\t");  // Tabulation pour une meilleure lisibilité
  Serial.print("Movement Category Y: ");
  Serial.println(movementCategoryY);

  // Convertir la position X du joystick en un angle pour le servomoteur
  int servoAngle = map(joystickXValue, 0, 1023, 0, 180);  // Mapper la valeur de 0 à 1023 à un angle de 0 à 180

  // Positionner les servomoteurs à l'angle calculé
  UpperLeftServo.write(servoAngle);
  UpperRightServo.write(servoAngle);
  DownRightServo.write(servoAngle);
  DownLeftServo.write(servoAngle);


  // Ajouter un petit délai pour la lisibilité et éviter des mouvements trop rapides
  delay(100);  // Délai de 100 ms pour rendre les mouvements plus fluides
}

// Fonction pour catégoriser les valeurs du joystick en fonction de la plage
int categorizeMovement(int value) {
  if (value > 750 && value <= 1023) {
    return FULL_GAUCHE;       // Full Gauche
  } else if (value > 600 && value <= 750) {
    return HALF_GAUCHE;       // Half Gauche
  } else if (value > 400 && value <= 600) {
    return AUCUN_MOUVEMENT;   // Aucun Mouvement
  } else if (value > 250 && value <= 400) {
    return HALF_DROITE;       // Half Droite
  } else if (value >= 0 && value <= 250) {
    return FULL_DROITE;       // Full Droite
  } else {
    return OUT_OF_RANGE;      // Hors de la plage (vérification de sécurité)
  }
}