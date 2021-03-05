
import 'dart:async';

import 'package:flutter/services.dart';

class FlutterMmapStream {
  static const MethodChannel _channel =
      const MethodChannel('flutter_mmap_stream');

  static Future<String> get platformVersion async {
    final String version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
}
