/*!Begin Snippet:file*/
/**
 * This class models a recording. It extends {@link CatalogItem} and
 * adds the following information:
 * <ol>
 * <li>the performer of the recording, a <code>String</code></li>
 * <li>the format of the recording, a <code>String</code></li>
 * </ol>
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see CatalogItem
 */
public class Recording extends CatalogItem  {

	/* Performer of the recording. */
	private String  performer;

	/* Format of the recording. */
	private String  format;

	/**
	 * Constructs an <code>Recording</code> object.
	 *
	 * @param initialCode  the code of the catalog item.
	 * @param initialTitle  the title of the catalog item.
	 * @param initialYear  the year of the catalog item.
	 * @param initialPerformer  the performer of the recording.
	 * @param initialFormat  the format of the recording.
	 */
	public Recording(String initialCode, String initialTitle,
			int initialYear, String initialPerformer,
			String initialFormat)  {

		super(initialCode, initialTitle, initialYear);

		this.performer = initialPerformer;
		this.format = initialFormat;
	}

	/**
	 * Returns the performer of this recording.
	 *
	 * @return  the performer of this recording.
	 */
	public String  getPerformer()  {

		return  this.performer;
	}

	/**
	 * Returns the format of this recording.
	 *
	 * @return  the format of this recording.
	 */
	public String  getFormat()  {

		return  this.format;
	}

	/**
	 * Returns the string representation of this recording.
	 *
	 * @return  the string representation of this recording.
	 */
	public String toString()  {

		return  super.toString() + "_" + getPerformer() + "_"
		        + getFormat();
	}
}
/*!End Snippet:file*/