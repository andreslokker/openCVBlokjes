# openCVBlokjes
Opencv blokjes beroepsproduct


# Hoe te compileren:
1. Open in deze folder een terminal en voer het commando "make" in.

# Hoe valt de applicatie op te starten (interactieve mode):
1. Open de terminal in de root folder van het project.
2. Voer het volgende commando uit (na het compileren): "./application".
3. Het programma zal eerst vragen of er nog een configuratiebestand gemaakt moet worden. Antwoorden met Y of N in console. Waar "Y" is ja en "N" is nee.

# Hoe valt de applicatie op te starten (batch mode):
1. Open de terminal in de root folder van het project.
2. Voer het volgende commando uit (na het compileren): "./application -batch locationOfFile".
3. Het programma zal eerst vragen of er nog een configuratiebestand gemaakt moet worden. Antwoorden met Y of N in console. Waar "Y" is ja en "N" is nee.


# Shapes en kleuren vinden
1. Voor het detecteren van de shapes zijn engelse termen gebruikt
	Vierkant = square
	Cirkel = circle
	Halve cirkel = semiCircle
	Rechthoek = rectangle
	Driehoek = triangle
2. Voor het detecteren van de kleuren zijn engelse termen gebruikt
	Rood = red
	Groen = green
	Geel = yellow
	Blauw = blue
	Zwart = black
	Wit = White
3. Voor het daadwerkelijk zoeken van een shape + kleur moet de input op de volgende wijze ingevoerd worden in de console:
	vorm[ws]kleur

# Configuratiebestand
1. Het configuratiebestand is als volgt opgebouwd: Per regel staat een kleurconfiguratie.
	De volgorde van de kleuren in het configuratiebestand is altijd: rood groen blauw geel zwart wit.
	Een kleurconfiguratie is als volgt opgebouwd: [naam kleur][ws][Hue min][ws][Hue max][ws][Saturation min][ws][Saturation max][ws][Value min][ws][Value max]

# Batchbestand
1. Het batchbestand is als volgt opgebouwd: Per regel staat een vorm + kleur
	Deze vorm+kleur moet altijd als volgt ingevoerd worden: [vorm][ws][kleur] (in het engels)
