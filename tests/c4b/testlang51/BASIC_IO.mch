MACHINE
  BASIC_IO
  /* pragma NO_CONVERGENCE */
  
SEES
b2rust_types

  


OPERATIONS

  /*----------------------------------------------------------------------**
  INTERVAL_READ: saisie d'un nombre dans (mm..nn). Le curseur reapparait a la
  position courante, l'operateur doit alors taper le nombre suivi de return,
  sans caracteres avant. Les caracteres apres le nombre sont ignores. Tant
  que le nombre n'est pas correct: message d'erreur "THIS IS NOT A VALUE IN
  mm..nn" et nouvelle saisie.
  **----------------------------------------------------------------------*/ 
  bb <-- INTERVAL_READ(mm,nn) = PRE
    nn: rust_u8 &
    mm: rust_u8 &
    mm<=nn &
    bb : rust_u8
  THEN
    bb:: mm..nn
  END;

  /*----------------------------------------------------------------------**
  INT_WRITE: ecriture d'un entier sur stdout, sans return.
  **----------------------------------------------------------------------*/ 
  INT_WRITE(vv) = PRE
    vv: rust_u8
  THEN
    skip
  END;

  /*----------------------------------------------------------------------**
  BOOL_READ: saisie de TRUE ou FALSE par l'operateur. Le curseur reapparait a
  la position courante, l'operateur doit alors taper TRUE ou FALSE en toutes 
  lettres. Tant que la saisie n'est pas correcte: message "THIS IS NOT A
  BOOL VALUE, TYPE TRUE OR FALSE" et nouvelle saisie.
  **----------------------------------------------------------------------*/ 
  bb <-- BOOL_READ = PRE
  	bb : BOOL
    THEN
    	skip
  END;

  /*----------------------------------------------------------------------**
  BOOL_WRITE: ecriture de TRUE ou FALSE en toutes lettres sur stdout, sans 
  return.
  **----------------------------------------------------------------------*/ 
  BOOL_WRITE(bb) = PRE
    bb: BOOL
  THEN
    skip
  END;

  /*----------------------------------------------------------------------**
  CHAR_READ: saisie de caracteres par l'operateur. Le premier CHAR_READ 
  provoque la reapparition du curseur a sa position courante, l'operateur
  fait une saisie terminee par return. A ce moment CHAR_READ retourne le
  premier caractere tape; les appels suivants a CHAR_READ retournent
  immediatement les caracteres consecutifs de la meme saisie, jusqu'au return
  compris. Le prochain CHAR_READ provoque une nouvelle saisie.
  **----------------------------------------------------------------------*/ 
/*  cc <-- CHAR_READ = PRE
    cc: rust_u8
    THEN
	skip
  END;*/

  /*----------------------------------------------------------------------**
  BOOL_WRITE: ecriture d'un caractere sur stdout.
  ATTENTION: ne pas utiliser de caractere entre quotes: par exemple:
  . CHAR_WRITE('n') n'a pas de sens.
  NOTA: CHAR_WRITE(10) est utilise pour imprimer un return.
  **----------------------------------------------------------------------*/ 
/*  CHAR_WRITE(cc) = PRE
    cc: rust_u8
  THEN
    skip
  END;
*/
  /*----------------------------------------------------------------------**
  STRING_WRITE: ecriture d'une chaine de caracteres sur stdout.
  En effet, les chaines de caracteres entre quotes sont valides dans la
  syntaxe B, avec les conventions
  .  \n = return
  .  \t = TAB
  .  \B = sonette
  .  \E = escape
  .  \" = "
  .  \\ = \
  exemple: STRING_WRITE("\tHello\n")
  NOTA: STRING_WRITE ne peut etre employe qu'avec un parametre litteral.
  STRING_WRITE(vv) ou vv est une variable causera une PO fausse.
  **----------------------------------------------------------------------*/ 
  STRING_WRITE(ss) = PRE
    ss: STRING
  THEN
    skip
  END

END
