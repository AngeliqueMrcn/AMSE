import 'package:flutter/material.dart';

// On veut naviguer entre les pages (deja fait donc affichage de "ok")

class DisplayImageWidget extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Mon application',
      home: Scaffold(
        appBar: AppBar(
          title: Text('Mon application'),
        ),
        body: Center(
          child: Text(
            'Ok',
            style: TextStyle(
              fontSize: 30.0,
            ),
          ),
        ),
      ),
    );
  }
}
