# Toepassingsopdracht Talen en Automaten
Groep: Inte, Jonas, Dzhem, Maksim

## Ideeën:
- Regex-herkenning in teksten
- Treinspoor verdeling / richting switcher 
- Kweken van een plant
- Email spam filter
- Autocorrectie
- Sorteer systemen
- Herkenning chemische elementen in materialen
- Simulatie groep organismen / opwarming van aarde
- Barcode converter tot passwoord/iets anders..., kan misschien samengehangen worden met sorteersysteem.
- Automatisch verwarming systeem -> waardes opmeten, meegeven aan FA's deze gebruiken om te zien wat er moet gebeuren met de waardes die ingelezen zijn
- Geautomatiseerd metro-station, ticketten scannen, kunnen ook liften, lichten, veiligheidsalarmeren in gebruikt worden enz. Dit kan dan ook allemaal geregeld worden door de FA's
  kunnen ook automaten worden toegevoegd worden om ticketten te kopen... enz.
  Bij het kopen en scannen van de ticketten kan dan bv een PDA gebruikt worden, enkel die ticketten die gekocht worden kunnen geaccepteerd worden door de ticketscanners aan de       ingangen.
  
  Veiligheidsalarmen, vooral aan de metrorails enz bv metro niet aan peron, mensen komen over een bepaalde grens wordt op een of andere reden gealarmeerd, handig voor blinden       mensen... kan dan ook gedaan worden met FA, final state wordt bereikt door geen metro aan station + wordt over grens gegaan. 
  
  lichten bijvoorbeeld voor de metro zelf, mag doorrijden of niet doorrijden enz...
  
  Liften kunnen gebruikt worden voor mensen die niet beschikbaar zijn voor de trap te nemen.
  
- Het herkennen van vliegtuig- en sattelietsignalen. Vliegtuigen (en allerlei spaceflight vehicles) en sattelieten zenden signalen in een bepaalde vorm die dan een code bevatten, 
  en d.m.v. FSM kan je bepalen waar ze vandaan komen (van welk land het vliegtuig is,...), xD je kan ook spion dingen opsporen (als je de signaalcode niet kent). (dit allemaal is voor uitbreiding vatbaar btw). 
  Je kan zelfs miss een databank opstellen met bepaalde gegevens en in die gegevens zoeken op die code.
  
- het zeven (ik weet niet of dit het juiste woord is) van allerlei stenen, aarde, zand. D.m.v. FSM (kijken naar kleur, dikte, massadichtheid,...) dan bepalen wat het is (gebruik in geologie, afvalverwerking,...). 
  De zeef zelf fungeert dan eigenlijk deels ook als een FSM. (voor uitbreiding vatbaar)
  
## Voorstellen
1) Herkenning chemische elementen: (Inte en Jonas)
We herkennen chemische elementen mbv DFA's. We kunnen voor elk chemisch element zijn eigen accepting state te maken of slechts voor de meeste basis-elementen één maken. We kunnen dan stoffen mbv xml-bestanden meegeven waarbij elke stof verschillende node's heeft met daarin de naam. Enkele features hiervan zijn:
  - Een overzicht geven van alle chemische elementen die aanwezig zijn met hoeveel procent ze voorkomen (wegschrijven naar een bestand of cout).
  - Opvragen of een chemische element aanwezig is in een bepaalde stof.
  - Herkenning van "valse" chemische elementen die niet bestaan.
  - Meerdere stoffen tegelijk inlezen in hetzelfde xml-bestand en overzicht hiervan wegschrijven.
  - NOG ANDERE SUGGESTIES
