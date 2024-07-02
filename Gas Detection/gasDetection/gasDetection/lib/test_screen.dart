import 'dart:developer';
import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:web_socket_channel/io.dart';

class TestScreen extends StatefulWidget {
  final String title;
  final String img;
  final Color color;
  const TestScreen(
      {super.key, required this.title, required this.img, required this.color});
// Declare a field that holds the Todo.
  @override
  State<TestScreen> createState() => _TestScreenState();
}

class _TestScreenState extends State<TestScreen> {
  late IOWebSocketChannel channel; //channel varaible for websocket
  bool connected = false; // boolean value to track connection status
  String wsUrl = "ws://192.168.0.191:8765";

  socketConnection() {
    try {
      channel = IOWebSocketChannel.connect(wsUrl);

      channel.stream.listen(
        (message) {
          log("message >> " + message);
          return;
        },
        onDone: () {
          log("Connection Closed");
          socketConnection();
        },
        onError: (error) {
          log(error.toString());
        },
      );
    } catch (error) {
      print(error);
    }
  }

  @override
  void initState() {
    socketConnection();
    super.initState();
  }

  @override
  void dispose() {
    channel.sink.close();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: const Text("AI"),
      ),
      body: Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
        Center(
          child: Text(
            widget.title,
            style: const TextStyle(fontSize: 32),
          ),
        ),
        Image.asset(widget.img),
      ]),
      bottomNavigationBar: Padding(
        padding: const EdgeInsets.all(8.0),
        child: ElevatedButton(
          style: ElevatedButton.styleFrom(
            backgroundColor: widget.color,
          ),
          onPressed: () {
            String jsonString =
                json.encode({"cmd": "test", "type": widget.title});
            channel.sink.add(jsonString);
            // channel.sink.close();
          },
          child: const Text('Test',
              style: TextStyle(fontSize: 24, color: Colors.white)),
        ),
      ),
    );
  }
}
