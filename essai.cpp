int main() {
	time_t heure_depart;
	heure_depart = time(NULL);


	cout << heure_depart;

	return 0;
}

//quand on cr�e le compte, on change la variable heure_depart � time(NULL)
//et quand on re-regarde le solde la fois d'apr�s, on change le solde � solde+(solde*(solde*(time(NULL)-heure_depart)))
//et on remet heure_depart � time(NULL)



