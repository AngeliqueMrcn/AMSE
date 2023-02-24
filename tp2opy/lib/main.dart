import 'package:flutter/material.dart';

// import 'util.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: Text("Afficher des images"),
        ),
        body: Image.asset('/home/angelique_mrcn/Documents/AMSE/tp2opy/assets/images/pic2.jpg'), 
      ),
    );
  }
}