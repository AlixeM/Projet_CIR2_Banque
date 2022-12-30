int main() {
	time_t heure_depart;
	heure_depart = time(NULL);


	cout << heure_depart;
	cout << " seconds has passed since 00:00:00 GMT, Jan 1, 1970";

	return 0;
}

//quand on change le solde sur le compte, on change la variable heure_depart à time(NULL)
//et quand on re-regarde le solde la fois d'après, on change le solde à solde+(solde*(solde*(time(NULL)-heure_depart)))
//et on remet heure_depart à time(NULL)
