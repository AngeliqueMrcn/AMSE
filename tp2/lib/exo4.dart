import 'package:flutter/material.dart';

//On veut afficher une tuile appartenant a une image 

class Tile {
  String imageURL;
  Alignment alignment;

  Tile({this.imageURL = 'assets/images/pic2.jpg', this.alignment = Alignment.center});

  Widget croppedImageTile() {
    return FittedBox(
      fit: BoxFit.fill,
      child: ClipRect(
        child: Container(
          child: Align(
            alignment: this.alignment,
            widthFactor: 0.3,
            heightFactor: 0.3,
            child: Image.network(this.imageURL),
          ),
        ),
      ),
    );
  }
}

//On doit mettre l'URL dans cette version, sinon marche pas
// Alignment(0,0) la meme que Alignment.center

Tile tile = new Tile(
    imageURL: 'assets/images/pic2.jpg', alignment: Alignment(0, 0));

class DisplayImageWidget extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Affichage d'un morceau d'image"),
        centerTitle: true,
      ),
      body: Center(
          child: Column(children: [
        SizedBox(
            width: 150.0,
            height: 150.0,
            child: Container(
                margin: EdgeInsets.all(20.0),
                child: this.createTileWidgetFrom(tile))),
        Container(
            height: 200,
            child: Image.network('assets/images/pic2.jpg',
                fit: BoxFit.cover))
      ])),
    );
  }

  Widget createTileWidgetFrom(Tile tile) {
    return InkWell(
      child: tile.croppedImageTile(),
      onTap: () {
        print("Tu as appuyé sur une touche");
      },
    );
  }
}
