import 'package:flutter/material.dart';
// import 'package:Taquin/util.dart';
import 'dart:math';

//On affiche une image au milieu de l'écran
//StatelessWidget est obligatoire pour l'affichage
// Il faut aussi un return Scaffold
// les arguments peuvent etre mis dans le désordre

class DisplayImageWidget extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text('Display image'),
        ),
        body: Center(
          child:
            Image.asset(
                'assets/images/0-Star-Wars-memes.jpeg',
                width: 350,
                fit: BoxFit.cover,
                ),
        ));
  }
}
