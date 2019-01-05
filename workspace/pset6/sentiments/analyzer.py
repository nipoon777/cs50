import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.pwords = set()
        self.nwords = set()
        file = open(positives,"r")
        for line in file:
            if (line.startswith(";"))== False:
                self.pwords.add(line.rstrip("\n"))
        file.close()

        file = open(negatives,"r")
        for line in file:
            if (line.startswith(";"))==False:
               self.nwords.add(line.rstrip("\n"))
        file.close()




        # TODO

    def analyze(self, tweet):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(tweet)
        i=0
        for word in tokens:
            if word.lower() in self.pwords:
                i+=1
            elif word.lower() in self.nwords:
                i+=-1
            else:
                continue
         # TODO
        return i
