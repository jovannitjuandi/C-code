    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    int n = 0;
    char name[MAX_SPECIES_NAME_LENGTH];
    char clean[MAX_SPECIES_NAME_LENGTH];
    char current[MAX_SPECIES_NAME_LENGTH];
    char compare[MAX_SPECIES_NAME_LENGTH];
    
    while (i < n_sightings) {
        strcpy (name, sightings[i].species);
        while (name [j] != '\0') {
            if (isalpha(name[j]) != 0) {
                clean[k] = tolower(name[j]);
                k = k + 1;
            }
            j = j + 1;
        }
        if (clean[k-1] != '\0') {
            clean[k] = '\0';
        }
        
        while (species_names_file[l] != EOF) {
            strcpy (current, species_names_file[l]);
            while (current[m] != EOF) {
                if (isalpha(current[m]) != 0) {
                    compare[n] = tolower(current[m]);
                    n = n + 1;
                }
                m = m + 1;
            }
            m = 0;
            if (compare[n-1] != '\0') {
                compare[n] = '\0';
            }
            n = 0;
            if (strcmp(compare, clean) == 0) {
                strcpy(sightings[i].species, current);
            }
            l = l + 1;
        }
        l = 0;
        
        j = 0;
        k = 0;
        clean[k] = '\0';
        i = i + 1;
    }
    
// 1 clear from punctuations
// 2 clear multiple spaces
// 3 only proper capital letters
/*void clear_name(char species_names_file[], int index, struct pod sightings[n_sightings]) {
    int i = 0;
    int j = 0;
    
    char name[MAX_SPECIES_NAME_LENGTH];
    char clean1[MAX_SPECIES_NAME_LENGTH];
    char clean2[MAX_SPECIES_NAME_LENGTH];
    char clean3[MAX_SPECIES_NAME_LENGTH];
    
    strcpy(name, sightings[index].species);
    
    // first cleaning
    while (name[i] != '\0') {
        if (isalpha(name[i]) != 0 || name[i] == 32) {
            clean1[j] = name[i];
            j = j + 1;
        }
        i = i + 1;
    }
    if (clean[j-1] != '\0') {
        clean[j] = '\0';
    }
    
    i = 0;
    j = 0;
    
    // second cleaning
    while (clean1[i] != '\0') {
    
    }
}*/
