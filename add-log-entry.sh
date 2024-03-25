# Get the current date
current_date=$(date +"%Y-%m-%d %H:%M:%S")

# Create a header with the current date
header="$current_date" 

# Prompt user for a title
read -p "Enter a title for this log entry: " title
read -p "Enter a short description: " description 
read -p "Describe how you feel/felt during today/task: " feelings 

# Specify the file to append the header and title to
log_file="log.md"

# Append the header and title to the log file
echo "" >> "$log_file" # Add a blank line for separation
echo "## $header" >> "$log_file"
echo "### $title" >> "$log_file"
echo "*Description*: $description" >> "$log_file"
echo "*Feelings*: $feelings" >> "$log_file"
echo "" >> "$log_file" # Add a blank line for separation

# Optionally, you can add some additional information or prompt for input here
echo "Log entry added for $current_date with title: $title."
