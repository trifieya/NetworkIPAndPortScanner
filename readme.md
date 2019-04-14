Lien Replit : https://repl.it/@eyatrifi/NetworkIPAndPortScanner

## La conception : ## 


**La fonction : scan_ipv4_adress()** 

scan_ipv4_adress()

{

afficher les adresses ipv4 connectées dans le réseau local : adresse IP et nom de la machine

exemple résultat [192.168.1.1:pc_aya,192.168.1.2:tel_aya]

enregister les résultats dans un fichier .log : résultat de scan + date de scan * *exemple [192.168.1.1:pc_aya,192.168.1.2:tel_aya] 14/04/2019 13:42 GMT+2* *

}


**La fonction : scan_ipv4_from_log(date_from,date_to)** 

{

Parcourir le contenu du fichier log et afficher les adresses IPv4 connectées dans le réseau local dans un intervalle du temps données

}


**La fonction : open_port_scanner()** 

{

Afficher les ports ouverts d'une adresse IP donnée dans un intervalle des numéros de ports

}
