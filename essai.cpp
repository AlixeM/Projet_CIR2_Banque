int main() {
	time_t heure_depart;
	heure_depart = time(NULL);


	cout << heure_depart;

	return 0;
}

//quand on crée le compte, on change la variable heure_depart à time(NULL)
//et quand on re-regarde le solde la fois d'après, on change le solde à solde+(solde*(solde*(time(NULL)-heure_depart)))
//et on remet heure_depart à time(NULL)



