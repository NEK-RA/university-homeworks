class Response:
  def __init__(self, content):
    self.data = content


class ResponseOk(Response):
  def __init__(self, content):
    super().__init__(content)


class ResponseBad(Response):
  def __init__(self, content):
    super().__init__(content)